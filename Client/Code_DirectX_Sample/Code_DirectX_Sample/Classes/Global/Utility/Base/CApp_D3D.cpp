#include "CApp_D3D.h"
#include "../../Access/Access+Global.h"
#include "../../Factory/Factory+Global.h"
#include "../Scene/CScene.h"
#include "../Light/CLight.h"
#include "../Camera/CCamera.h"
#include "../Manager/CManager_Res.h"
#include "../Manager/CManager_Time.h"
#include "../Manager/CManager_Input.h"

CApp_D3D::CApp_D3D(HINSTANCE a_hInst,
	int a_nOpt_Show, const SIZE& a_rstSize_Wnd) : CApp_Wnd(a_hInst, a_nOpt_Show, a_rstSize_Wnd)
{
	this->SetColor_Clear(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	ZeroMemory(&m_stParams_Present, sizeof(m_stParams_Present));
}

CApp_D3D::~CApp_D3D(void)
{
	this->Release(true);
}

void CApp_D3D::Init(void)
{
	CApp_Wnd::Init();

	m_pScene = this->CreateScene();
	m_pLight = this->CreateLight();
	m_pCamera = this->CreateCamera();
	m_pFactory = this->CreateFactory();

	m_pDevice = this->CreateDevice();
	m_pSwapChain = this->CreateSwapChain();

	m_pXFont = this->CreateXFont();
	m_pXSprite = this->CreateXSprite();

	m_pD3D = this->CreateD3D();
	m_pDevice9 = this->CreateDevice9();
}

void CApp_D3D::UpdateState_Light(void)
{
	// Do Something
}

void CApp_D3D::UpdateState_Camera(void)
{
	// 상태 갱신이 불가능 할 경우
	if(!GET_MANAGER_INPUT()->IsDown_MouseBtn(EMouseBtn::RIGHT))
	{
		return;
	}

	auto stDirection = VEC_ZERO;

	float fDelta_MouseX = GET_MANAGER_INPUT()->GetDelta_MouseX();
	float fDelta_MouseY = GET_MANAGER_INPUT()->GetDelta_MouseY();

	// 상 / 하 키를 눌렀을 경우
	if(GET_MANAGER_INPUT()->IsDown_Key(DIK_W) || GET_MANAGER_INPUT()->IsDown_Key(DIK_S))
	{
		float fSign = GET_MANAGER_INPUT()->IsDown_Key(DIK_W) ? 1.0f : -1.0f;
		stDirection += m_pCamera->GetVec_Forward() * fSign;
	}

	// 좌 / 우 키를 눌렀을 경우
	if(GET_MANAGER_INPUT()->IsDown_Key(DIK_A) || GET_MANAGER_INPUT()->IsDown_Key(DIK_D))
	{
		float fSign = GET_MANAGER_INPUT()->IsDown_Key(DIK_A) ? -1.0f : 1.0f;
		stDirection += m_pCamera->GetVec_Right() * fSign;
	}

	// 상 / 하강 키를 눌렀을 경우
	if(GET_MANAGER_INPUT()->IsDown_Key(DIK_Q) || GET_MANAGER_INPUT()->IsDown_Key(DIK_E))
	{
		float fSign = GET_MANAGER_INPUT()->IsDown_Key(DIK_Q) ? 1.0f : -1.0f;
		stDirection += VEC_WORLD_UP * fSign;
	}

	D3DXVec3Normalize(&stDirection, &stDirection);
	auto stPos = m_pCamera->GetPos();

	m_pCamera->SetPos(stPos + (stDirection * 250.0f * GET_MANAGER_TIME()->GetTime_Delta()));

	auto stVec_Up = VEC_WORLD_UP;
	auto stVec_Right = m_pCamera->GetVec_Right();
	auto stMatrix_OriginRotate = m_pCamera->GetMatrix_Rotate();

	D3DXQUATERNION stQuaternion_Yaw;

	D3DXQuaternionRotationAxis(&stQuaternion_Yaw,
		&stVec_Up, D3DXToRadian(fDelta_MouseX * 90.0f * GET_MANAGER_TIME()->GetTime_Delta()));

	D3DXQUATERNION stQuaternion_Pitch;

	D3DXQuaternionRotationAxis(&stQuaternion_Pitch,
		&stVec_Right, D3DXToRadian(fDelta_MouseY * 90.0f * GET_MANAGER_TIME()->GetTime_Delta()));

	D3DXQUATERNION stQuaternion_Origin;
	D3DXQuaternionRotationMatrix(&stQuaternion_Origin, &stMatrix_OriginRotate);

	auto stQuaternion = stQuaternion_Origin * stQuaternion_Yaw * stQuaternion_Pitch;

	D3DXMATRIXA16 stMatrix_Rotate;
	D3DXMatrixRotationQuaternion(&stMatrix_Rotate, &stQuaternion);

	float fAngle_X = asinf(-stMatrix_Rotate._32);
	float fAngle_Y = 0.0f;
	float fAngle_Z = 0.0f;

	if(cosf(fAngle_X) > 0.0001f)
	{
		fAngle_Y = atan2f(stMatrix_Rotate._31, stMatrix_Rotate._33);
		fAngle_Z = atan2f(stMatrix_Rotate._12, stMatrix_Rotate._22);
	}
	else
	{
		fAngle_Y = atan2f(-stMatrix_Rotate._13, stMatrix_Rotate._11);
	}

	m_pCamera->SetRotate(D3DXVECTOR3(D3DXToDegree(fAngle_X), D3DXToDegree(fAngle_Y), D3DXToDegree(fAngle_Z)));
}

void CApp_D3D::Release(bool a_bIsDestroy)
{
	SAFE_RELEASE(m_pView_RT);
	SAFE_RELEASE(m_pView_DS);

	// 제거 모드 일 경우
	if(a_bIsDestroy)
	{
		SAFE_DEL(m_pScene);
		SAFE_DEL(m_pLight);
		SAFE_DEL(m_pCamera);

		SAFE_RELEASE(m_pDevice);
		SAFE_RELEASE(m_pFactory);
		SAFE_RELEASE(m_pSwapChain);

		SAFE_RELEASE(m_pD3D);
		SAFE_RELEASE(m_pDevice9);
	}
}

void CApp_D3D::Update(float a_fTime_Delta)
{
	char szStr_DebugInfo[MAX_PATH] = "";

	sprintf(szStr_DebugInfo, "Delta Time: %f sec\nRunning Time: %f sec",
		a_fTime_Delta, CManager_Time::GetInst()->GetTime_Running());

	m_oStr_DebugInfo = szStr_DebugInfo;
	m_pScene->Update(a_fTime_Delta);
}

void CApp_D3D::LateUpdate(float a_fTime_Delta)
{
	this->UpdateState_Light();
	this->UpdateState_Camera();

	m_pScene->Update(a_fTime_Delta);
}

void CApp_D3D::Render(HDC a_hDC)
{
	m_pDevice->OMSetRenderTargets(1, &m_pView_RT, m_pView_DS);
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDevice->ClearRenderTargetView(m_pView_RT, m_stColor_Clear);
	m_pDevice->ClearDepthStencilView(m_pView_DS, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	auto stMatrix_View = m_pCamera->GetMatrix_View();
	auto stMatrix_Projection = m_pCamera->GetMatrix_Projection();

	for(auto& rstValType : GET_MANAGER_RES()->GetEffects())
	{
		auto pCBuffer_ViewMatrix = rstValType.second->GetConstantBufferByName(NAME_VIEW_MATRIX_CBUFFER.c_str())->AsMatrix();
		pCBuffer_ViewMatrix->SetMatrix(stMatrix_View);

		auto pCBuffer_ProjectionMatrix = rstValType.second->GetConstantBufferByName(NAME_PROJECTION_MATRIX_CBUFFER.c_str())->AsMatrix();
		pCBuffer_ProjectionMatrix->SetMatrix(stMatrix_Projection);
	}

	this->Render(m_pDevice);
	m_pScene->Render(m_pDevice);
}

void CApp_D3D::LateRender(HDC a_hDC)
{
	this->LateRender(m_pDevice);
	m_pScene->LateRender(m_pDevice);

	UINT nXFlags_Sprite = D3DX10_SPRITE_SAVE_STATE | 
		D3DX10_SPRITE_SORT_TEXTURE | D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT;

	m_pXSprite->Begin(nXFlags_Sprite);
	
	RECT stRect_DebugInfo;
	ZeroMemory(&stRect_DebugInfo, sizeof(stRect_DebugInfo));

	m_pXFont->DrawTextA(nullptr,
		m_oStr_DebugInfo.c_str(), m_oStr_DebugInfo.size(), &stRect_DebugInfo, DT_TOP | DT_LEFT | DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pXFont->DrawTextA(nullptr,
		m_oStr_DebugInfo.c_str(), m_oStr_DebugInfo.size(), &stRect_DebugInfo, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	this->LateRender(m_pXSprite);
	m_pScene->LateRender(m_pXSprite);

	m_pXSprite->End();
}

void CApp_D3D::SetupDevice(void)
{
	DXGI_SWAP_CHAIN_DESC stDesc_SwapChain;
	m_pSwapChain->GetDesc(&stDesc_SwapChain);

	HRESULT nResult = m_pSwapChain->ResizeBuffers(0, 
		this->GetSize_Wnd().cx, this->GetSize_Wnd().cy, stDesc_SwapChain.BufferDesc.Format, stDesc_SwapChain.Flags);

	m_pView_RT = this->CreateView_RT();
	m_pView_DS = this->CreateView_DS();

	m_stParams_Present.BackBufferWidth = this->GetSize_Wnd().cx;
	m_stParams_Present.BackBufferHeight = this->GetSize_Wnd().cy;

	m_pDevice9->Reset(&m_stParams_Present);
	m_pDevice9->Reset(&m_stParams_Present);
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

	this->SetupDevice();
	this->SetupCamera();
	this->SetupViewport();
}

std::string CApp_D3D::GetPath_Effect(void)
{
	return STR_EMPTY;
}

void CApp_D3D::SetScene(CScene* a_pScene)
{
	// 씬 변경이 불가능 할 경우
	if(a_pScene == m_pScene || a_pScene == m_pScene_Next)
	{
		return;
	}

	m_pScene_Next = a_pScene;
}

CScene* CApp_D3D::CreateScene(void)
{
	auto pScene = new CScene();
	return pScene;
}

CLight* CApp_D3D::CreateLight(void)
{
	auto pLight = new CLight();
	pLight->SetRotate(D3DXVECTOR3(45.0f, 45.0f, 0.0f));

	return pLight;
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

	stDesc_SwapChain.SampleDesc.Quality = Access::GetLevels_MultiSampleQuality(stDesc_SwapChain.BufferDesc.Format,
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
	ID3D10Texture2D* pBuffer_DS = Factory::CreateTexture2D(this->GetSize_Wnd().cx,
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

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCaps_Device);

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

	m_stParams_Present.MultiSampleQuality = Access::GetLevels_MultiSampleQuality(m_stParams_Present.BackBufferFormat,
		m_stParams_Present.MultiSampleType) - 1;

	DWORD nFlags_Create = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 하드웨어 연산을 지원 할 경우
	if(stCaps_Device.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nFlags_Create = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	m_pD3D->CreateDevice(stCaps_Device.AdapterOrdinal,
		stCaps_Device.DeviceType, this->GetHandle_Wnd(), nFlags_Create | D3DCREATE_MULTITHREADED, &m_stParams_Present, &pDevice);

	return pDevice;
}

void CApp_D3D::Present(HDC a_hSrcDC, HDC a_hDestDC)
{
	m_pSwapChain->Present(0, 0);

	// 씬 전환이 불가능 할 경우
	if(m_pScene_Next == nullptr)
	{
		return;
	}

	SAFE_DEL(m_pScene);

	m_pScene = m_pScene_Next;
	m_pScene = nullptr;
}
