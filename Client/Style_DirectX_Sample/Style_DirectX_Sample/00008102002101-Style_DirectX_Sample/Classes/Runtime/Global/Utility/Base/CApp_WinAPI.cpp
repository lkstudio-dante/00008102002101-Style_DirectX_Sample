#include "CApp_WinAPI.h"

#include "../Manager/CManager_Time.h"
#include "../Manager/CManager_Snd.h"
#include "../Manager/CManager_Input.h"
#include "../Manager/CManager_WinAPIRes.h"

// 전역 변수
static CApp_WinAPI* g_pInst = nullptr;

/** 윈도우 프로시저 */
static LRESULT CALLBACK WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams)
{
	static CApp_WinAPI* pApp_Wnd = nullptr;

	switch(a_nMsg)
	{
		case WM_CREATE:
			auto pstCreateStruct = (LPCREATESTRUCT)a_lParams;
			pApp_Wnd = (CApp_WinAPI*)pstCreateStruct->lpCreateParams;

			break;
	}

	return (pApp_Wnd != nullptr) ?
		pApp_Wnd->WndProc(a_hWnd, a_nMsg, a_wParams, a_lParams) : DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_WinAPI::CApp_WinAPI(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd)
	:
	m_hInst(a_hInst),
	m_nOpt_Show(a_nOpt_Show),
	m_stSize_Wnd(a_rstSize_Wnd)
{
	assert(g_pInst == nullptr);
	g_pInst = this;

	AllocConsole();
	m_pstWStream = freopen(::G_N_F_STREAM_CONSOLE_OUTPUT, "w", stdout);

	ZeroMemory(&m_stMsg, sizeof(m_stMsg));
	ZeroMemory(&m_stWndCls, sizeof(m_stWndCls));
	ZeroMemory(&m_stRect_Wnd, sizeof(m_stRect_Wnd));
}

CApp_WinAPI::~CApp_WinAPI(void)
{
	this->Release();
	this->Destroy();
}

void CApp_WinAPI::Init(void)
{
	m_hWnd = this->CreateWnd(&m_stWndCls);
}

void CApp_WinAPI::LateInit(void)
{
	ShowWindow(m_hWnd, m_nOpt_Show);

	GET_MANAGER_SND()->Init();
	GET_MANAGER_TIME()->Init();
	GET_MANAGER_INPUT()->Init();
	GET_MANAGER_WIN_API_RES()->Init();
}

void CApp_WinAPI::Release(void)
{
	// Do Something
}

void CApp_WinAPI::Destroy(void)
{
	FreeConsole();
	UnregisterClass(m_stWndCls.lpszClassName, m_hInst);

	SAFE_CLOSE(m_pstWStream);
}

void CApp_WinAPI::Update(void)
{
	// Do Something
}

void CApp_WinAPI::LateUpdate(void)
{
	// Do Something
}

void CApp_WinAPI::Render(void)
{
	// Do Something
}

void CApp_WinAPI::LateRender(void)
{
	// Do Something
}

int CApp_WinAPI::Run(void)
{
	this->Init();
	this->LateInit();

	UpdateWindow(m_hWnd);
	return this->RunLoop_Msg();
}

LRESULT CApp_WinAPI::WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams)
{
	switch(a_nMsg)
	{
		case WM_SIZE:
			this->HandleMsg_Size(a_hWnd, a_wParams, a_lParams);
			break;

		case WM_DESTROY:
			this->HandleMsg_Destroy(a_hWnd, a_wParams, a_lParams);
			break;
	}

	return DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_WinAPI* CApp_WinAPI::GetInst(void)
{
	return g_pInst;
}

bool CApp_WinAPI::IsQuit_App(void)
{
	return m_stMsg.message == WM_QUIT;
}

void CApp_WinAPI::HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	m_stSize_Wnd.cx = m_stRect_Wnd.right = LOWORD(a_lParams);
	m_stSize_Wnd.cy = m_stRect_Wnd.bottom = HIWORD(a_lParams);
}

void CApp_WinAPI::HandleMsg_Destroy(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	PostQuitMessage(0);
}

HWND CApp_WinAPI::CreateWnd(WNDCLASS* a_pstOutWndCls)
{
	WNDCLASS stWndCls =
	{
		CS_VREDRAW | CS_HREDRAW,
		::WndProc,
		0,
		0,
		m_hInst,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)GetStockObject(COLOR_WINDOW + 1),
		_T(""),
		_T("Example")
	};

	RegisterClass(&stWndCls);
	CopyMemory(a_pstOutWndCls, &stWndCls, sizeof(stWndCls));

	RECT stRect_Wnd =
	{
		0, 0, m_stSize_Wnd.cx, m_stSize_Wnd.cy
	};

	AdjustWindowRect(&stRect_Wnd, WS_OVERLAPPEDWINDOW, false);

	return CreateWindow(stWndCls.lpszClassName,
		stWndCls.lpszClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, stRect_Wnd.right - stRect_Wnd.left, stRect_Wnd.bottom - stRect_Wnd.top, GetDesktopWindow(), nullptr, this->GetHandle_Inst(), this);
}

void CApp_WinAPI::Present(void)
{
	StretchBlt(m_hDC,
		0, 0, m_stSize_Wnd.cx, m_stSize_Wnd.cy, m_hDC_Memory, 0, 0, m_stSize_Wnd.cx, m_stSize_Wnd.cy, SRCCOPY);
}

int CApp_WinAPI::RunLoop_Msg(void)
{
	do
	{
		// 메세지가 존재 할 경우
		if(PeekMessage(&m_stMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_stMsg);
			DispatchMessage(&m_stMsg);
		}

		m_hDC = GetDC(m_hWnd);
		m_hDC_Memory = CreateCompatibleDC(m_hDC);

		auto hBitmap = CreateCompatibleBitmap(m_hDC, m_stSize_Wnd.cx, m_stSize_Wnd.cy);

		__try
		{
			SelectObject(m_hDC_Memory, hBitmap);
			FillRect(m_hDC_Memory, &m_stRect_Wnd, m_stWndCls.hbrBackground);

			GET_MANAGER_TIME()->Update();
			GET_MANAGER_INPUT()->Update();

			this->Update();
			this->LateUpdate();

			this->Render();
			this->LateRender();

			this->Present();
		}
		__finally
		{
			DeleteObject(hBitmap);

			DeleteDC(m_hDC_Memory);
			ReleaseDC(m_hWnd, m_hDC);
		}
	} while(!this->IsQuit_App());

	return m_stMsg.wParam;
}
