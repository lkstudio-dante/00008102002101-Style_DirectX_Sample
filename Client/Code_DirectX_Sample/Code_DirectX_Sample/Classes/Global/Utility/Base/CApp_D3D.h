#pragma once

#include "CApp_Wnd.h"
#include "../../Define/KDefine+Global.h"

class CLight;
class CCamera;

/**
 * Direct 3D 어플리케이션
 */
class CApp_D3D : public CApp_Wnd
{
public:

	using CApp_Wnd::Render;
	using CApp_Wnd::LateRender;

public:			// IReleasable

	/** 해제한다 */
	virtual void Release(bool a_bIsDestroy = false) override;

public:			// IUpdatable

	/** 상태를 갱신한다 */
	virtual void Update(float a_fTime_Delta) override;

public:			// IRenderable

	/** 객체를 그린다 */
	virtual void Render(HDC a_hDC) final override;

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) final override;

public:   // public 함수

	/** 배경색 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, Color_Clear, m_stColor_Clear, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	/** 광원 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CLight*, Light, m_pLight, nullptr);

	/** 카메라 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CCamera*, Camera, m_pCamera, nullptr);

	/** Direct 3D 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3D9, D3D, m_pD3D, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3DDEVICE9, Device, m_pDevice, nullptr);

	/** 폰트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPD3DXFONT, XFont, m_pXFont, nullptr);

	/** 스프라이트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPD3DXSPRITE, XSprite, m_pXSprite, nullptr);

public:			// public 함수

	/** 생성자 */
	CApp_D3D(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	virtual ~CApp_D3D(void);

	/** 초기화 */
	virtual void Init(void) final override;

	/** 초기화 */
	virtual void LateInit(void) override;

protected:			// protected 함수

	/** 디바이스를 변경한다 */
	virtual void SetupDevice(void);

	/** 카메라를 설정한다 */
	virtual void SetupCamera(void);

	/** 뷰 포트를 설정한다 */
	virtual void SetupViewport(void);

	/** 크기 메세지를 처리한다 */
	virtual void HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams) override;

protected:			// protected 접근 함수

	/** 이펙트 경로를 반환한다 */
	virtual std::string GetPath_Effect(void);

protected:			// protected 팩토리 함수

	/** 광원을 생성한다 */
	virtual CLight* CreateLight(void);

	/** 카메라를 생성한다 */
	virtual CCamera* CreateCamera(void);

	/** Direct 3D 을 생성한다 */
	virtual LPDIRECT3D9 CreateD3D(void);

	/** 디바이스를 생성한다 */
	virtual LPDIRECT3DDEVICE9 CreateDevice(void);

	/** 폰트를 생성한다 */
	virtual LPD3DXFONT CreateXFont(void);

	/** 스프라이트를 생성한닫 */
	virtual LPD3DXSPRITE CreateXSprite(void);

private:			// private 함수

	/** 화면을 출력한다 */
	virtual void Present(HDC a_hSrcDC, HDC a_hDestDC) override;

private:			// private 변수

	std::string m_oStrDebugInfo = STR_EMPTY;
	D3DPRESENT_PARAMETERS m_stParams_Present;
};
