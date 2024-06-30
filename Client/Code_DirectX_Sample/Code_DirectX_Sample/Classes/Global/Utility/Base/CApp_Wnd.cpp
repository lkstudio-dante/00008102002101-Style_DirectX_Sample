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
	static CApp_Wnd* pApp_Wnd = nullptr;

	switch(a_nMsg)
	{
		case WM_CREATE:
			auto pstCreateStruct = (LPCREATESTRUCT)a_lParams;
			pApp_Wnd = (CApp_Wnd*)pstCreateStruct->lpCreateParams;

			break;
	}

	return (pApp_Wnd != nullptr) ?
		pApp_Wnd->WndProc(a_hWnd, a_nMsg, a_wParams, a_lParams) : DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_Wnd::CApp_Wnd(HINSTANCE a_hInst,
	int a_nOpt_Show, const SIZE& a_rstSize_Wnd) : m_hInst(a_hInst), m_nOpt_Show(a_nOpt_Show), m_stSize_Wnd(a_rstSize_Wnd)
{
	assert(g_pInst == nullptr);
	g_pInst = this;

	// 콘솔이 생성되었을 경우
	if(AllocConsole())
	{
		m_pstWStream = freopen("CONOUT$", "w", stdout);
	}

	ZeroMemory(&m_stRect_Wnd, sizeof(m_stRect_Wnd));
	ZeroMemory(&m_stWndCls, sizeof(m_stWndCls));
}

CApp_Wnd::~CApp_Wnd(void)
{
	FreeConsole();
	SAFE_CLOSE(m_pstWStream);
	UnregisterClass(m_stWndCls.lpszClassName, m_hInst);
}

void CApp_Wnd::Init(void)
{
	m_hWnd = this->CreateWnd(&m_stWndCls);
}

void CApp_Wnd::LateInit(void)
{
	ShowWindow(m_hWnd, m_nOpt_Show);

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
	return this->RunLoop_Msg();
}

LRESULT CApp_Wnd::WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams)
{
	switch(a_nMsg)
	{
		case WM_SIZE: this->HandleMsg_Size(a_hWnd, a_wParams, a_lParams); break;
		case WM_DESTROY: this->HandleMsg_Destroy(a_hWnd, a_wParams, a_lParams); break;
	}

	return DefWindowProc(a_hWnd, a_nMsg, a_wParams, a_lParams);
}

CApp_Wnd* CApp_Wnd::GetInst(void)
{
	return g_pInst;
}

int CApp_Wnd::RunLoop_Msg(void)
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
		auto hDC_Memory = CreateCompatibleDC(hDC);

		auto hBitmap = CreateCompatibleBitmap(hDC, m_stSize_Wnd.cx, m_stSize_Wnd.cy);

		__try
		{
			SelectObject(hDC_Memory, hBitmap);
			FillRect(hDC_Memory, &m_stRect_Wnd, m_stWndCls.hbrBackground);

			CManager_Time::GetInst()->Update(0.0f);
			CManager_Input::GetInst()->Update(0.0f);

			this->Update(CManager_Time::GetInst()->GetTime_Delta());
			this->LateUpdate(CManager_Time::GetInst()->GetTime_Delta());

			this->Render(hDC_Memory);
			this->LateRender(hDC_Memory);

			this->Present(hDC_Memory, hDC);
		}
		__finally
		{
			DeleteDC(hDC_Memory);
			DeleteObject(hBitmap);

			ReleaseDC(m_hWnd, hDC);
		}
	}

	return stMsg.wParam;
}

void CApp_Wnd::HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	m_stSize_Wnd.cx = m_stRect_Wnd.right = LOWORD(a_lParams);
	m_stSize_Wnd.cy = m_stRect_Wnd.bottom = HIWORD(a_lParams);
}

void CApp_Wnd::HandleMsg_Destroy(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams)
{
	PostQuitMessage(0);
}

HWND CApp_Wnd::CreateWnd(WNDCLASS* a_pstOutWndCls)
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

void CApp_Wnd::Present(HDC a_hSrcDC, HDC a_hDestDC)
{
	StretchBlt(a_hDestDC,
		0, 0, m_stSize_Wnd.cx, m_stSize_Wnd.cy, a_hSrcDC, 0, 0, m_stSize_Wnd.cx, m_stSize_Wnd.cy, SRCCOPY);
}
