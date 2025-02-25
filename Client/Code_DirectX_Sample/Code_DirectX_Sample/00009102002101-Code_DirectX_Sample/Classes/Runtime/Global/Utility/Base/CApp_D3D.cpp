#include "CApp_D3D.h"

#include "../../Access/CAccess+DirectX_Abs.h"
#include "../../Factory/CFactory+DirectX_Abs.h"

#include "../Camera/CCamera.h"

#include "../Manager/CManager_Time.h"
#include "../Manager/CManager_D3DRes.h"

CApp_D3D::CApp_D3D(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd)
	:
	CApp_WinAPI(a_hInst, a_nOpt_Show, a_rstSize_Wnd)
{
	this->SetColor_Clear(::G_COLOR_GRAY);
	ZeroMemory(&m_stParams_Present, sizeof(m_stParams_Present));
}

CApp_D3D::~CApp_D3D(void)
{
	// Do Something
}

void CApp_D3D::Init(void)
{
	CApp_WinAPI::Init();
	m_pFactory = this->CreateFactory();

	m_pDevice = this->CreateDevice();
	m_pSwapChain = this->CreateSwapChain();
	m_pState_DS = this->CreateState_DS();

	m_pXFont = this->CreateXFont();
	m_pXSprite = this->CreateXSprite();

	m_pD3D9 = this->CreateD3D();
	m_pDevice9 = this->CreateDevice9();
}

void CApp_D3D::LateInit(void)
{
	CApp_WinAPI::LateInit();
	GET_MANAGER_D3D_RES()->Init();
}

void CApp_D3D::Release(void)
{
	CApp_WinAPI::Release();

	SAFE_RELEASE(m_pView_RT);
	SAFE_RELEASE(m_pView_DS);
}

void CApp_D3D::Destroy(void)
{
	CApp_WinAPI::Destroy();
	SAFE_RELEASE(m_pState_DS);

	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pFactory);
	SAFE_RELEASE(m_pSwapChain);

	SAFE_RELEASE(m_pD3D9);
	SAFE_RELEASE(m_pDevice9);
}

void CApp_D3D::Update(void)
{
	CApp_WinAPI::Update();
	char szStr_DebugInfo[MAX_PATH] = "";

	sprintf(szStr_DebugInfo, "Delta Time: %f sec\nRunning Time: %f sec",
		GET_MANAGER_TIME()->GetTime_Delta(), CManager_Time::GetInst()->GetTime_Running());

	m_oStr_DebugInfo = szStr_DebugInfo;
}

void CApp_D3D::LateUpdate(void)
{
	CApp_WinAPI::LateUpdate();
}

void CApp_D3D::Render(void)
{
	CApp_WinAPI::Render();

	m_pDevice->OMSetRenderTargets(1, &m_pView_RT, m_pView_DS);
	m_pDevice->OMSetDepthStencilState(m_pState_DS, 0);

	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDevice->ClearRenderTargetView(m_pView_RT, m_stColor_Clear);
	m_pDevice->ClearDepthStencilView(m_pView_DS, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
}

void CApp_D3D::LateRender(void)
{
	CApp_WinAPI::LateRender();

	UINT nXFlags_Sprite = D3DX10_SPRITE_SAVE_STATE |
		D3DX10_SPRITE_SORT_TEXTURE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT;

	m_pXSprite->Begin(nXFlags_Sprite);

	__try
	{
		RECT stRect_DebugInfo;
		ZeroMemory(&stRect_DebugInfo, sizeof(stRect_DebugInfo));

		m_pXFont->DrawTextA(nullptr,
			m_oStr_DebugInfo.c_str(), m_oStr_DebugInfo.size(), &stRect_DebugInfo, DT_TOP | DT_LEFT | DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pXFont->DrawTextA(nullptr,
			m_oStr_DebugInfo.c_str(), m_oStr_DebugInfo.size(), &stRect_DebugInfo, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	__finally
	{
		m_pXSprite->End();
	}
}

void CApp_D3D::ResetDevice(void)
{
	DXGI_SWAP_CHAIN_DESC stDesc_SwapChain;
	m_pSwapChain->GetDesc(&stDesc_SwapChain);

	m_pSwapChain->ResizeBuffers(stDesc_SwapChain.BufferCount,
		this->GetSize_Wnd().cx, this->GetSize_Wnd().cy, stDesc_SwapChain.BufferDesc.Format, stDesc_SwapChain.Flags);

	m_pView_RT = this->CreateView_RT();
	m_pView_DS = this->CreateView_DS();

	// 디바이스 9 를 설정한다 {
	m_stParams_Present.BackBufferWidth = this->GetSize_Wnd().cx;
	m_stParams_Present.BackBufferHeight = this->GetSize_Wnd().cy;

	m_pDevice9->Reset(&m_stParams_Present);
	m_pDevice9->Reset(&m_stParams_Present);
	// 디바이스 9 를 설정한다 }
}

void CApp_D3D::ResetCamera(void)
{
	// Do Something
}

void CApp_D3D::ResetViewport(void)
{
	D3D10_VIEWPORT stViewport;
	ZeroMemory(&stViewport, sizeof(stViewport));

	stViewport.TopLeftX = 0;
	stViewport.TopLeftY = 0;

	stViewport.Width = this->GetSize_Wnd().cx;
	stViewport.Height = this->GetSize_Wnd().cy;

	stViewport.MinDepth = 0.0f;
	stViewport.MaxDepth = 1.0f;

	m_pDevice->RSSetViewports(1, &stViewport);
}

void CApp_D3D::HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	CApp_WinAPI::HandleMsg_Size(a_hWnd, a_wParams, a_lParams);
	this->Release();

	this->ResetDevice();
	this->ResetCamera();
	this->ResetViewport();
}

std::string CApp_D3D::GetPath_Effect(void)
{
	return ::G_STR_EMPTY;
}

IDXGIFactory* CApp_D3D::CreateFactory(void)
{
	IDXGIFactory* pFactory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)&pFactory);

	return pFactory;
}

IDXGISwapChain* CApp_D3D::CreateSwapChain(void)
{
	DXGI_SWAP_CHAIN_DESC stDesc_SwapChain;
	ZeroMemory(&stDesc_SwapChain, sizeof(stDesc_SwapChain));

	stDesc_SwapChain.Windowed = true;
	stDesc_SwapChain.OutputWindow = this->GetHandle_Wnd();
	stDesc_SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	stDesc_SwapChain.Flags = 0;

	stDesc_SwapChain.BufferCount = 1;
	stDesc_SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	stDesc_SwapChain.BufferDesc.Width = this->GetSize_Wnd().cx;
	stDesc_SwapChain.BufferDesc.Height = this->GetSize_Wnd().cy;
	stDesc_SwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	stDesc_SwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	stDesc_SwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	stDesc_SwapChain.BufferDesc.RefreshRate.Numerator = 1;
	stDesc_SwapChain.BufferDesc.RefreshRate.Denominator = 60;

	stDesc_SwapChain.SampleDesc.Count = 1;

	stDesc_SwapChain.SampleDesc.Quality = CAccess::GetLevels_MultiSampleQuality(stDesc_SwapChain.BufferDesc.Format,
		stDesc_SwapChain.SampleDesc.Count) - 1;

	IDXGISwapChain* pSwapChain = nullptr;
	m_pFactory->CreateSwapChain(m_pDevice, &stDesc_SwapChain, &pSwapChain);

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
	ID3D10Texture2D* pBuffer_Back = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBuffer_Back);

	ID3D10RenderTargetView* pView_RT = nullptr;
	m_pDevice->CreateRenderTargetView(pBuffer_Back, nullptr, &pView_RT);

	SAFE_RELEASE(pBuffer_Back);
	return pView_RT;
}

ID3D10DepthStencilView* CApp_D3D::CreateView_DS(void)
{
	ID3D10Texture2D* pBuffer_DS = CFactory::CreateTexture2D(this->GetSize_Wnd().cx,
		this->GetSize_Wnd().cy, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D10_BIND_DEPTH_STENCIL);

	D3D10_TEXTURE2D_DESC stDesc_DSBuffer;
	pBuffer_DS->GetDesc(&stDesc_DSBuffer);

	D3D10_DEPTH_STENCIL_VIEW_DESC stDesc_DSView;
	ZeroMemory(&stDesc_DSView, sizeof(stDesc_DSView));

	stDesc_DSView.Format = stDesc_DSBuffer.Format;
	stDesc_DSView.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	stDesc_DSView.Texture2D.MipSlice = 0;

	ID3D10DepthStencilView* pView_DS = nullptr;
	m_pDevice->CreateDepthStencilView(pBuffer_DS, &stDesc_DSView, &pView_DS);

	SAFE_RELEASE(pBuffer_DS);
	return pView_DS;
}

ID3D10DepthStencilState* CApp_D3D::CreateState_DS(void)
{
	D3D10_DEPTH_STENCIL_DESC stDesc_DS;
	ZeroMemory(&stDesc_DS, sizeof(stDesc_DS));

	stDesc_DS.DepthEnable = true;
	stDesc_DS.DepthFunc = D3D10_COMPARISON_LESS;
	stDesc_DS.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;

	ID3D10DepthStencilState* pState_DS = nullptr;
	m_pDevice->CreateDepthStencilState(&stDesc_DS, &pState_DS);

	return pState_DS;
}

ID3DX10Font* CApp_D3D::CreateXFont(void)
{
	D3DX10_FONT_DESCA stXDesc_Font;
	ZeroMemory(&stXDesc_Font, sizeof(stXDesc_Font));

	stXDesc_Font.Width = 0;
	stXDesc_Font.Height = 22;
	stXDesc_Font.Weight = FW_BOLD;
	stXDesc_Font.CharSet = DEFAULT_CHARSET;
	stXDesc_Font.Quality = CLEARTYPE_NATURAL_QUALITY;
	stXDesc_Font.OutputPrecision = OUT_DEFAULT_PRECIS;

	ID3DX10Font* pXFont = nullptr;
	D3DX10CreateFontIndirectA(m_pDevice, &stXDesc_Font, &pXFont);

	return pXFont;
}

ID3DX10Sprite* CApp_D3D::CreateXSprite(void)
{
	ID3DX10Sprite* pXSprite = nullptr;
	D3DX10CreateSprite(m_pDevice, 0, &pXSprite);

	return pXSprite;
}

LPDIRECT3D9 CApp_D3D::CreateD3D(void)
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CApp_D3D::CreateDevice9(void)
{
	D3DCAPS9 stCaps_Device;
	ZeroMemory(&stCaps_Device, sizeof(stCaps_Device));

	m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCaps_Device);

	m_stParams_Present.Windowed = true;
	m_stParams_Present.hDeviceWindow = this->GetHandle_Wnd();
	m_stParams_Present.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_stParams_Present.Flags = 0;

	m_stParams_Present.EnableAutoDepthStencil = true;
	m_stParams_Present.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_stParams_Present.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_stParams_Present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_stParams_Present.BackBufferCount = 1;
	m_stParams_Present.BackBufferWidth = this->GetSize_Wnd().cx;
	m_stParams_Present.BackBufferHeight = this->GetSize_Wnd().cy;
	m_stParams_Present.BackBufferFormat = D3DFMT_A8R8G8B8;

	m_stParams_Present.MultiSampleType = D3DMULTISAMPLE_NONE;

	m_stParams_Present.MultiSampleQuality = CAccess::GetLevels_MultiSampleQuality(m_stParams_Present.BackBufferFormat,
		m_stParams_Present.MultiSampleType) - 1;

	DWORD nFlags_Create = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 하드웨어 연산을 지원 할 경우
	if(stCaps_Device.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nFlags_Create = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	m_pD3D9->CreateDevice(stCaps_Device.AdapterOrdinal,
		stCaps_Device.DeviceType, this->GetHandle_Wnd(), nFlags_Create | D3DCREATE_MULTITHREADED, &m_stParams_Present, &pDevice);

	return pDevice;
}

void CApp_D3D::Present(void)
{
	m_pSwapChain->Present(0, 0);
}
