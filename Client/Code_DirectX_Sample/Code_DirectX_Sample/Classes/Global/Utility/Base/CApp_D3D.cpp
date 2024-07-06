#include "CApp_D3D.h"
#include "../../Access/Access+Global.h"
#include "../../Factory/Factory+Global.h"
#include "../Manager/CManager_Res.h"
#include "../Manager/CManager_Time.h"
#include "../Manager/CManager_Input.h"
#include "../Light/CLight.h"
#include "../Camera/CCamera.h"

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

	m_pLight = this->CreateLight();
	m_pCamera = this->CreateCamera();

	m_pD3D = this->CreateD3D();
	m_pDevice = this->CreateDevice();
}

void CApp_D3D::LateInit(void)
{
	CApp_Wnd::LateInit();
	this->SetupDevice();
}

void CApp_D3D::Release(bool a_bIsDestroy)
{
	SAFE_RELEASE(m_pXFont);
	SAFE_RELEASE(m_pXSprite);

	// 제거 모드 일 경우
	if(a_bIsDestroy)
	{
		SAFE_DEL(m_pLight);
		SAFE_DEL(m_pCamera);

		SAFE_RELEASE(m_pD3D);
		SAFE_RELEASE(m_pDevice);
	}
}

void CApp_D3D::Update(float a_fTime_Delta)
{
	m_pCamera->Update(a_fTime_Delta);
	char szStrDebugInfo[MAX_PATH] = "";

	sprintf(szStrDebugInfo, "Delta Time: %f sec\nRunning Time: %f sec",
		a_fTime_Delta, CManager_Time::GetInst()->GetTime_Running());

	m_oStrDebugInfo = szStrDebugInfo;
}

void CApp_D3D::Render(HDC a_hDC)
{
	m_pDevice->Clear(0, 
		nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, m_stColor_Clear, 1.0f, 0);

	auto stMatrix_View = m_pCamera->GetMatrix_View();
	auto stMatrix_Projection = m_pCamera->GetMatrix_Projection();

	for(auto& rstValType : GET_MANAGER_RES()->GetXEffects())
	{
		rstValType.second->SetMatrix(NAME_VIEW_MATRIX_CBUFFER.c_str(), &stMatrix_View);
		rstValType.second->SetMatrix(NAME_PROJECTION_MATRIX_CBUFFER.c_str(), &stMatrix_Projection);
	}

	m_pDevice->BeginScene();
	this->Render(m_pDevice);
}

void CApp_D3D::LateRender(HDC a_hDC)
{
	this->LateRender(m_pDevice);
	m_pXSprite->Begin(D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

	RECT stRectDebugInfo;
	ZeroMemory(&stRectDebugInfo, sizeof(stRectDebugInfo));

	m_pXFont->DrawTextA(nullptr,
		m_oStrDebugInfo.c_str(), m_oStrDebugInfo.size(), &stRectDebugInfo, DT_TOP | DT_LEFT | DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pXFont->DrawTextA(nullptr,
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
	m_stParams_Present.BackBufferWidth = this->GetSize_Wnd().cx;
	m_stParams_Present.BackBufferHeight = this->GetSize_Wnd().cy;

	m_pDevice->Reset(&m_stParams_Present);
	m_pDevice->Reset(&m_stParams_Present);

	m_pXFont = this->CreateXFont();
	m_pXSprite = this->CreateXSprite();

	for(auto& rstValType : GET_MANAGER_RES()->GetXEffects())
	{
		rstValType.second->OnLostDevice();
	}
}

void CApp_D3D::SetupCamera(void)
{
	// Do Something
}

void CApp_D3D::SetupViewport(void)
{
	D3DVIEWPORT9 stViewport;
	ZeroMemory(&stViewport, sizeof(stViewport));

	stViewport.X = 0;
	stViewport.Y = 0;

	stViewport.Width = this->GetSize_Wnd().cx;
	stViewport.Height = this->GetSize_Wnd().cy;

	stViewport.MinZ = 0.0f;
	stViewport.MaxZ = 1.0f;

	m_pCamera->SetViewport(stViewport);
	m_pDevice->SetViewport(&stViewport);
}

void CApp_D3D::HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	CApp_Wnd::HandleMsg_Size(a_hWnd, a_wParams, a_lParams);
	this->Release();

	this->SetupDevice();
	this->SetupCamera();
	this->SetupViewport();
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

LPDIRECT3D9 CApp_D3D::CreateD3D(void)
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 CApp_D3D::CreateDevice(void)
{
	D3DCAPS9 stCaps_Device;
	ZeroMemory(&stCaps_Device, sizeof(stCaps_Device));

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps_Device);

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

LPD3DXFONT CApp_D3D::CreateXFont(void)
{
	D3DXFONT_DESCA stXDesc_Font;
	ZeroMemory(&stXDesc_Font, sizeof(stXDesc_Font));

	stXDesc_Font.Width = 0;
	stXDesc_Font.Height = 22;
	stXDesc_Font.Weight = FW_BOLD;
	stXDesc_Font.CharSet = DEFAULT_CHARSET;
	stXDesc_Font.Quality = CLEARTYPE_NATURAL_QUALITY;
	stXDesc_Font.OutputPrecision = OUT_DEFAULT_PRECIS;

	LPD3DXFONT pXFont = nullptr;
	D3DXCreateFontIndirectA(m_pDevice, &stXDesc_Font, &pXFont);

	return pXFont;
}

LPD3DXSPRITE CApp_D3D::CreateXSprite(void)
{
	LPD3DXSPRITE pXSprite = nullptr;
	D3DXCreateSprite(m_pDevice, &pXSprite);

	return pXSprite;
}

void CApp_D3D::Present(HDC a_hSrcDC, HDC a_hDestDC)
{
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
