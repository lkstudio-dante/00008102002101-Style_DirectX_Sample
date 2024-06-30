#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IReleasable.h"
#include "../Interface/IUpdateable.h"
#include "../Interface/IRenderable.h"

/**
 * 윈도우 어플리케이션
 */
class CApp_Wnd : public virtual IReleasable, public virtual IUpdateable, public virtual IRenderable
{
public:   // public 함수

	/** 윈도우 크기 프로퍼티 */
	GETTER_PROPERTY(SIZE, Size_Wnd, m_stSize_Wnd);

	/** 윈도우 영역 프로퍼티 */
	GETTER_PROPERTY(RECT, Rect_Wnd, m_stRect_Wnd);

	/** 윈도우 클래스 프로퍼티 */
	GETTER_PROPERTY(WNDCLASS, WndCls, m_stWndCls);

	/** 출력 옵션 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(int, Opt_Show, m_nOpt_Show, 0);

	/** 윈도우 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HWND, Handle_Wnd, m_hWnd, nullptr);

	/** 인스턴스 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HINSTANCE, Handle_Inst, m_hInst, nullptr);

public:			// public 함수

	/** 생성자 */
	CApp_Wnd(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	virtual ~CApp_Wnd(void);

	/** 초기화 */
	virtual void Init(void);

	/** 초기화 */
	virtual void LateInit(void);

	/** 앱을 실행한다 */
	int Run(void);

	/** 윈도우 프로시저 */
	virtual LRESULT WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams);

public:			// public 접근 함수

	/** 인스턴스를 반환한다 */
	static CApp_Wnd* GetInst(void);

protected:			// protected 함수

	/** 메세지 루프를 실행한다 */
	virtual int RunLoop_Msg(void);

	/** 크기 메세지를 처리한다 */
	virtual void HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams);

	/** 제거 메세지를 처리한다 */
	virtual void HandleMsg_Destroy(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams);

protected:			// protected 팩토리 함수

	/** 윈도우를 생성한다 */
	virtual HWND CreateWnd(WNDCLASS* a_pstOutWndCls);

private:			// private 함수

	/** 화면을 출력한다 */
	virtual void Present(HDC a_hSrcDC, HDC a_hDestDC);

private:			// private 변수

	FILE* m_pstWStream = nullptr;
};
