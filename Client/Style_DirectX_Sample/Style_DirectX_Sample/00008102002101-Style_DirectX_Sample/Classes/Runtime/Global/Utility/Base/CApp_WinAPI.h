#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "CObj.h"

#include "../Interface/IPresentable.h"
#include "../Interface/IRenderable_WinAPI.h"

/**
* 윈도우즈 API 어플리케이션
*/
class CApp_WinAPI : public CObj, 
	public virtual IPresentable, public virtual IRenderable_WinAPI
{
public:

	using IRenderable_WinAPI::Render;
	using IRenderable_WinAPI::LateRender;

public:   // public 함수

	/** 생성자 */
	CApp_WinAPI(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	virtual ~CApp_WinAPI(void) = 0;

	/** 초기화 */
	virtual void Init(void) override;

	/** 초기화 */
	virtual void LateInit(void) override;

	/** 리소스를 해제한다 */
	virtual void Release(void) override;

	/** 객체를 제거한다 */
	virtual void Destroy(void) override;

	/** 상태를 갱신한다 */
	virtual void Update(void) override;

	/** 상태를 갱신한다 */
	virtual void LateUpdate(void) override;

	/** 객체를 그린다 */
	virtual void Render(void) override;

	/** 객체를 그린다 */
	virtual void LateRender(void) override;

	/** 앱을 실행한다 */
	int Run(void);

	/** 윈도우 프로시저 */
	virtual LRESULT WndProc(HWND a_hWnd, UINT a_nMsg, WPARAM a_wParams, LPARAM a_lParams);

	/** 윈도우 크기 프로퍼티 */
	GETTER_PROPERTY(SIZE, Size_Wnd, m_stSize_Wnd);

	/** 윈도우 영역 프로퍼티 */
	GETTER_PROPERTY(RECT, Rect_Wnd, m_stRect_Wnd);

	/** 윈도우 클래스 프로퍼티 */
	GETTER_PROPERTY(WNDCLASS, WndCls, m_stWndCls);

	/** 출력 옵션 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(int, Opt_Show, m_nOpt_Show, 0);

	/** 디바이스 컨텍스트 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HDC, Handle_DC, m_hDC, nullptr);

	/** 메모리 디바이스 컨텍스트 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HDC, Handle_MemoryDC, m_hDC_Memory, nullptr);

	/** 윈도우 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HWND, Handle_Wnd, m_hWnd, nullptr);

	/** 인스턴스 핸들 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(HINSTANCE, Handle_Inst, m_hInst, nullptr);

public:			// public 접근 함수

	/** 인스턴스를 반환한다 */
	static CApp_WinAPI* GetInst(void);

protected:			// protected 함수

	/** 앱 종료 여부를 검사한다 */
	virtual bool IsQuit_App(void);

	/** 크기 메세지를 처리한다 */
	virtual void HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams);

	/** 제거 메세지를 처리한다 */
	virtual void HandleMsg_Destroy(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams);

protected:			// protected 팩토리 함수

	/** 윈도우를 생성한다 */
	virtual HWND CreateWnd(WNDCLASS* a_pstOutWndCls);

private:			// IPresentable

	/** 화면을 출력한다 */
	virtual void Present(void) override;

private:			// private 함수

	/** 메세지 루프를 실행한다 */
	virtual int RunLoop_Msg(void);

private:			// private 변수

	MSG m_stMsg;
	FILE* m_pstWStream = nullptr;
};
