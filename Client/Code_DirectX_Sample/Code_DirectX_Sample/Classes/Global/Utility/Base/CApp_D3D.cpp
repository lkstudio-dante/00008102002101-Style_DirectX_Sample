#include "CApp_D3D.h"
#include "../../Access/Access+Global.h"
#include "../../Factory/Factory+Global.h"
#include "../Manager/CManager_Res.h"
#include "../Manager/CManager_Time.h"
#include "../Camera/CCamera.h"

CApp_D3D::CApp_D3D(HINSTANCE a_hInst,
	int a_nOpt_Show, const SIZE& a_rstSize_Wnd) : CApp_Wnd(a_hInst, a_nOpt_Show, a_rstSize_Wnd)
{
	this->SetColorClear(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
}

CApp_D3D::~CApp_D3D(void)
{
	this->Release(true);
}

void CApp_D3D::Init(void)
{
	CApp_Wnd::Init();

	m_pCamera = this->CreateCamera();
	m_pFactory = this->CreateFactory();

	m_pDevice = this->CreateDevice();
	m_pSwapChain = this->CreateSwapChain();

	m_pState_DS = this->CreateState_DS();
	m_pState_Rasterizer = this->CreateState_Rasterizer();

	m_pXFont = this->CreateXFont();
	m_pXSprite = this->CreateXSprite();
}

void CApp_D3D::LateInit(void)
{
	CApp_Wnd::LateInit();
	this->SetupDevice();
}

void CApp_D3D::Release(bool a_bIsDestroy)
{
	SAFE_RELEASE(m_pD3D9);
	SAFE_RELEASE(m_pDevice9);

	SAFE_RELEASE(m_pView_RT);
	SAFE_RELEASE(m_pView_DS);

	// 제거 모드 일 경우
	if(a_bIsDestroy)
	{
		SAFE_DEL(m_pCamera);

		SAFE_RELEASE(m_pXFont);
		SAFE_RELEASE(m_pXSprite);

		SAFE_RELEASE(m_pState_DS);
		SAFE_RELEASE(m_pState_Rasterizer);

		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pFactory);
		SAFE_RELEASE(m_pSwapChain);
	}
}

void CApp_D3D::Update(float a_fTime_Delta)
{
	char szStrDebugInfo[MAX_PATH] = "";

	sprintf(szStrDebugInfo, "Delta Time: %f sec\nRunning Time: %f sec",
		a_fTime_Delta, CManager_Time::GetInst()->GetTime_Running());

	m_oStrDebugInfo = szStrDebugInfo;
}

void CApp_D3D::Render(HDC a_hDC)
{
	m_pDevice->RSSetState(m_pState_Rasterizer);
	m_pDevice->OMSetDepthStencilState(m_pState_DS, 0);

	m_pDevice->OMSetRenderTargets(1, &m_pView_RT, m_pView_DS);
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDevice->ClearRenderTargetView(m_pView_RT, m_stColorClear);
	m_pDevice->ClearDepthStencilView(m_pView_DS, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	for(auto& rstValType : GET_MANAGER_RES()->GetEffects())
	{
		auto pCBuffer_ViewMatrix = rstValType.second->GetConstantBufferByName(NAME_VIEW_MATRIX_CBUFFER.c_str())->AsMatrix();
		pCBuffer_ViewMatrix->SetMatrix(m_pCamera->GetMatrix_View());

		auto pCBuffer_ProjectionMatrix = rstValType.second->GetConstantBufferByName(NAME_PROJECTION_MATRIX_CBUFFER.c_str())->AsMatrix();
		pCBuffer_ProjectionMatrix->SetMatrix(m_pCamera->GetMatrix_Projection());
	}

	this->Render(m_pDevice);
}

void CApp_D3D::LateRender(HDC a_hDC)
{
	this->LateRender(m_pDevice);
	m_pXSprite->Begin(D3DX10_SPRITE_SORT_TEXTURE | D3DX10_SPRITE_SAVE_STATE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT);

	RECT stRectDebugInfo;
	ZeroMemory(&stRectDebugInfo, sizeof(stRectDebugInfo));

	m_pXFont->DrawTextA(m_pXSprite,
		m_oStrDebugInfo.c_str(), m_oStrDebugInfo.size(), &stRectDebugInfo, DT_TOP | DT_LEFT | DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pXFont->DrawTextA(m_pXSprite,
		m_oStrDebugInfo.c_str(), m_oStrDebugInfo.size(), &stRectDebugInfo, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	this->LateRender(m_pXSprite);
	m_pXSprite->End();
}

std::string CApp_D3D::GetPath_Effect(void)
{
	return STR_EMPTY;
}

void CApp_D3D::SetupDevice(void)
{
	m_pView_RT = this->CreateView_RT();
	m_pView_DS = this->CreateView_DS();

	m_pD3D9 = this->CreateD3D9();
	m_pDevice9 = this->CreateDevice9();

	this->SetupCamera();
	this->SetupViewport();
}

void CApp_D3D::SetupCamera(void)
{
	// Do Something
}

void CApp_D3D::SetupViewport(void)
{
	D3D10_VIEWPORT stViewport;
	ZeroMemory(&stViewport, sizeof(stViewport));

	stViewport.TopLeftX = 0;
	stViewport.TopLeftY = 0;

	stViewport.Width = this->GetSize_Wnd().cx;
	stViewport.Height = this->GetSize_Wnd().cy;

	stViewport.MinDepth = 0.0f;
	stViewport.MaxDepth = 1.0f;

	m_pCamera->SetViewport(stViewport);
	m_pDevice->RSSetViewports(1, &stViewport);
}

void CApp_D3D::HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	CApp_Wnd::HandleMsg_Size(a_hWnd, a_wParams, a_lParams);
	this->Release();

	DXGI_SWAP_CHAIN_DESC stDescSwapChain;
	m_pSwapChain->GetDesc(&stDescSwapChain);

	m_pSwapChain->ResizeBuffers(0,
		this->GetSize_Wnd().cx, this->GetSize_Wnd().cy, stDescSwapChain.BufferDesc.Format, stDescSwapChain.Flags);

	this->SetupDevice();
}

CCamera* CApp_D3D::CreateCamera(void)
{
	auto pCamera = new CCamera();
	pCamera->SetFOV(D3DXToDegree(D3DX_PI / 4.0f));
	pCamera->SetPos(D3DXVECTOR3(0.0f, 0.0f, -pCamera->GetDistance()));

	return pCamera;
}

IDXGIFactory* CApp_D3D::CreateFactory(void)
{
	IDXGIFactory* pFactory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)&pFactory);

	return pFactory;
}

IDXGISwapChain* CApp_D3D::CreateSwapChain(void)
{
	DXGI_SWAP_CHAIN_DESC stDescSwapChain;
	ZeroMemory(&stDescSwapChain, sizeof(stDescSwapChain));

	stDescSwapChain.Windowed = true;
	stDescSwapChain.OutputWindow = this->GetHandle_Wnd();
	stDescSwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	stDescSwapChain.Flags = 0;

	stDescSwapChain.BufferCount = 1;
	stDescSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	stDescSwapChain.BufferDesc.Width = this->GetSize_Wnd().cx;
	stDescSwapChain.BufferDesc.Height = this->GetSize_Wnd().cy;
	stDescSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	stDescSwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	stDescSwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	stDescSwapChain.BufferDesc.RefreshRate.Numerator = 1;
	stDescSwapChain.BufferDesc.RefreshRate.Denominator = 60;

	stDescSwapChain.SampleDesc.Count = 1;

	stDescSwapChain.SampleDesc.Quality = Access::GetLevels_MultiSampleQuality(stDescSwapChain.BufferDesc.Format,
		stDescSwapChain.SampleDesc.Count) - 1;

	IDXGISwapChain* pSwapChain = nullptr;
	m_pFactory->CreateSwapChain(m_pDevice, &stDescSwapChain, &pSwapChain);

	return pSwapChain;
}

ID3D10Device* CApp_D3D::CreateDevice(void)
{
	IDXGIAdapter* pAdapter = nullptr;
	std::vector<IDXGIAdapter*> oVectorAdapters;

	for(int i = 0; SUCCEEDED(m_pFactory->EnumAdapters(i, &pAdapter)); ++i)
	{
		oVectorAdapters.push_back(pAdapter);
	}

	ID3D10Device* pDevice = nullptr;

	D3D10CreateDevice(oVectorAdapters.front(),
		D3D10_DRIVER_TYPE_HARDWARE, nullptr, 0, D3D10_SDK_VERSION, &pDevice);

	for(auto pAdapter : oVectorAdapters)
	{
		SAFE_RELEASE(pAdapter);
	}

	return pDevice;
}

ID3D10RenderTargetView* CApp_D3D::CreateView_RT(void)
{
	ID3D10Texture2D* pBufferBack = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBufferBack);

	ID3D10RenderTargetView* pView_RT = nullptr;
	m_pDevice->CreateRenderTargetView(pBufferBack, nullptr, &pView_RT);

	SAFE_RELEASE(pBufferBack);
	return pView_RT;
}

ID3D10DepthStencilView* CApp_D3D::CreateView_DS(void)
{
	auto pBufferDS = Factory::CreateTexture2D(this->GetSize_Wnd().cx,
		this->GetSize_Wnd().cy, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D10_BIND_DEPTH_STENCIL, FLAGS_CPU_ACCESS_NONE);

	D3D10_TEXTURE2D_DESC stDescDSBuffer;
	pBufferDS->GetDesc(&stDescDSBuffer);

	D3D10_DEPTH_STENCIL_VIEW_DESC stDescDSView;
	ZeroMemory(&stDescDSView, sizeof(stDescDSView));

	stDescDSView.Format = stDescDSBuffer.Format;
	stDescDSView.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	stDescDSView.Texture2D.MipSlice = 0;

	ID3D10DepthStencilView* pView_DS = nullptr;
	m_pDevice->CreateDepthStencilView(pBufferDS, &stDescDSView, &pView_DS);

	SAFE_RELEASE(pBufferDS);
	return pView_DS;
}

ID3D10DepthStencilState* CApp_D3D::CreateState_DS(void)
{
	D3D10_DEPTH_STENCIL_DESC stDescDS;
	ZeroMemory(&stDescDS, sizeof(stDescDS));

	ID3D10DepthStencilState* pState_DS = nullptr;
	m_pDevice->CreateDepthStencilState(&stDescDS, &pState_DS);

	return pState_DS;
}

ID3D10RasterizerState* CApp_D3D::CreateState_Rasterizer(void)
{
	D3D10_RASTERIZER_DESC stDescRasterizer;
	ZeroMemory(&stDescRasterizer, sizeof(stDescRasterizer));

	stDescRasterizer.CullMode = D3D10_CULL_BACK;
	stDescRasterizer.FillMode = D3D10_FILL_SOLID;

	ID3D10RasterizerState* pState_Rasterizer = nullptr;
	m_pDevice->CreateRasterizerState(&stDescRasterizer, &pState_Rasterizer);

	return pState_Rasterizer;
}

ID3DX10Font* CApp_D3D::CreateXFont(void)
{
	D3DX10_FONT_DESC stXDescFont;
	ZeroMemory(&stXDescFont, sizeof(stXDescFont));

	stXDescFont.Width = 0;
	stXDescFont.Height = 22;
	stXDescFont.Weight = FW_BOLD;
	stXDescFont.CharSet = DEFAULT_CHARSET;
	stXDescFont.Quality = CLEARTYPE_NATURAL_QUALITY;
	stXDescFont.OutputPrecision = OUT_DEFAULT_PRECIS;

	ID3DX10Font* pXFont = nullptr;
	D3DX10CreateFontIndirect(m_pDevice, &stXDescFont, &pXFont);

	return pXFont;
}

ID3DX10Sprite* CApp_D3D::CreateXSprite(void)
{
	ID3DX10Sprite* pXSprite = nullptr;
	D3DX10CreateSprite(m_pDevice, 0, &pXSprite);

	return pXSprite;
}

LPDIRECT3D9 CApp_D3D::CreateD3D9(void)
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CApp_D3D::CreateDevice9(void)
{
	D3DCAPS9 stCapsDevice;
	ZeroMemory(&stCapsDevice, sizeof(stCapsDevice));

	m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCapsDevice);

	D3DPRESENT_PARAMETERS stParams;
	ZeroMemory(&stParams, sizeof(stParams));

	stParams.Windowed = true;
	stParams.hDeviceWindow = this->GetHandle_Wnd();
	stParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stParams.Flags = 0;

	stParams.EnableAutoDepthStencil = true;
	stParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	stParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	stParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	stParams.BackBufferCount = 1;
	stParams.BackBufferWidth = this->GetSize_Wnd().cx;
	stParams.BackBufferHeight = this->GetSize_Wnd().cy;
	stParams.BackBufferFormat = D3DFMT_A8R8G8B8;

	stParams.MultiSampleType = D3DMULTISAMPLE_NONE;

	stParams.MultiSampleQuality = Access::GetLevels_MultiSampleQuality(stParams.BackBufferFormat,
		stParams.MultiSampleType) - 1;

	DWORD nFlagsCreate = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 하드웨어 연산을 지원 할 경우
	if(stCapsDevice.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nFlagsCreate = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	m_pD3D9->CreateDevice(stCapsDevice.AdapterOrdinal,
		stCapsDevice.DeviceType, this->GetHandle_Wnd(), nFlagsCreate | D3DCREATE_MULTITHREADED, &stParams, &pDevice);

	return pDevice;
}

void CApp_D3D::Present(HDC a_hSrcDC, HDC a_hDestDC)
{
	m_pSwapChain->Present(0, 0);
}
