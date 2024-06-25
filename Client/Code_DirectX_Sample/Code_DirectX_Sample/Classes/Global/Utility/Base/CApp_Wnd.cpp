#include "CApp_Wnd.h"
#include "../Manager/CManager_Res.h"
#include "../Manager/CManager_Snd.h"
#include "../Manager/CManager_Time.h"
#include "../Manager/CManager_Input.h"

// 전역 변수
static CApp_Wnd* g_pInst = nullptr;

/** 윈도우 프로시저 */
static LRESULT CALLBACK WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams)
{
	static CApp_Wnd* pAppWnd = nullptr;

	switch(a_nMsg)
	{
		case WM_CREATE:
			auto pstCreateStruct = (LPCREATESTRUCT)a_lParams;
			pAppWnd = (CApp_Wnd*)pstCreateStruct->lpCreateParams;

			break;
	}

	return (pAppWnd != nullptr) ?
		pAppWnd->WndProc(a_hWnd, a_nMsg, a_wParams, a_lParams) : DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_Wnd::CApp_Wnd(HINSTANCE a_hInst,
	int a_nOptShow, const SIZE& a_rstSizeWnd) : m_hInst(a_hInst), m_nOptShow(a_nOptShow), m_stSizeWnd(a_rstSizeWnd)
{
	assert(g_pInst == nullptr);
	g_pInst = this;

	// 콘솔이 생성되었을 경우
	if(AllocConsole())
	{
		m_pstWStream = freopen("CONOUT$", "w", stdout);
	}

	ZeroMemory(&m_stRectWnd, sizeof(m_stRectWnd));
	ZeroMemory(&m_stWndClass, sizeof(m_stWndClass));
}

CApp_Wnd::~CApp_Wnd(void)
{
	FreeConsole();
	SAFE_CLOSE(m_pstWStream);
	UnregisterClass(m_stWndClass.lpszClassName, m_hInst);
}

void CApp_Wnd::Init(void)
{
	m_hWnd = this->CreateWnd(&m_stWndClass);
}

void CApp_Wnd::LateInit(void)
{
	ShowWindow(m_hWnd, m_nOptShow);

	CManager_Res::GetInst()->Init();
	CManager_Snd::GetInst()->Init();
	CManager_Time::GetInst()->Init();
	CManager_Input::GetInst()->Init();
}

int CApp_Wnd::Run(void)
{
	this->Init();
	this->LateInit();

	UpdateWindow(m_hWnd);
	return this->RunLoopMsg();
}

LRESULT CApp_Wnd::WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams)
{
	switch(a_nMsg)
	{
		case WM_SIZE: this->HandleMsgSize(a_hWnd, a_wParams, a_lParams); break;
		case WM_DESTROY: this->HandleMsgDestroy(a_hWnd, a_wParams, a_lParams); break;
	}

	return DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_Wnd* CApp_Wnd::GetInst(void)
{
	return g_pInst;
}

int CApp_Wnd::RunLoopMsg(void)
{
	MSG stMsg;
	ZeroMemory(&stMsg, sizeof(stMsg));

	while(stMsg.message != WM_QUIT)
	{
		// 메세지가 존재 할 경우
		if(PeekMessage(&stMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&stMsg);
			DispatchMessage(&stMsg);
		}

		auto hDC = GetDC(m_hWnd);
		auto hMemDC = CreateCompatibleDC(hDC);
		auto hBitmap = CreateCompatibleBitmap(hDC, m_stSizeWnd.cx, m_stSizeWnd.cy);

		__try
		{
			SelectObject(hMemDC, hBitmap);
			FillRect(hMemDC, &m_stRectWnd, m_stWndClass.hbrBackground);

			CManager_Time::GetInst()->OnUpdate(0.0f);
			CManager_Input::GetInst()->OnUpdate(0.0f);

			this->OnUpdate(CManager_Time::GetInst()->GetTimeDelta());
			this->OnLateUpdate(CManager_Time::GetInst()->GetTimeDelta());

			this->OnRender(hMemDC);
			this->OnLateRender(hMemDC);

			this->Present(hMemDC, hDC);
		}
		__finally
		{
			DeleteDC(hMemDC);
			DeleteObject(hBitmap);

			ReleaseDC(m_hWnd, hDC);
		}
	}

	return stMsg.wParam;
}

void CApp_Wnd::HandleMsgSize(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	m_stSizeWnd.cx = m_stRectWnd.right = LOWORD(a_lParams);
	m_stSizeWnd.cy = m_stRectWnd.bottom = HIWORD(a_lParams);
}

void CApp_Wnd::HandleMsgDestroy(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	PostQuitMessage(0);
}

HWND CApp_Wnd::CreateWnd(WNDCLASS* a_pstOutClassWnd)
{
	WNDCLASS stClassWnd =
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

	RegisterClass(&stClassWnd);
	CopyMemory(a_pstOutClassWnd, &stClassWnd, sizeof(stClassWnd));

	RECT stRectWnd =
	{
		0, 0, m_stSizeWnd.cx, m_stSizeWnd.cy
	};

	AdjustWindowRect(&stRectWnd, WS_OVERLAPPEDWINDOW, false);

	return CreateWindow(stClassWnd.lpszClassName,
		stClassWnd.lpszClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, stRectWnd.right - stRectWnd.left, stRectWnd.bottom - stRectWnd.top, GetDesktopWindow(), nullptr, this->GetHandleInst(), this);
}

void CApp_Wnd::Present(HDC a_hSrcDC, HDC a_hDestDC)
{
	StretchBlt(a_hDestDC,
		0, 0, m_stSizeWnd.cx, m_stSizeWnd.cy, a_hSrcDC, 0, 0, m_stSizeWnd.cx, m_stSizeWnd.cy, SRCCOPY);
}
