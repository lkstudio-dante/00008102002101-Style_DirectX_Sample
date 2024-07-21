#pragma once

#include "CApp_Wnd.h"
#include "../../Define/KDefine+Global.h"

class CScene;
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

	/** 상태를 갱신한다 */
	virtual void LateUpdate(float a_fTime_Delta) override;

public:			// IRenderable

	/** 객체를 그린다 */
	virtual void Render(HDC a_hDC) final override;

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) final override;

public:   // public 함수

	/** 배경색 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, Color_Clear, m_stColor_Clear, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	/** 씬 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CScene*, Scene, m_pScene, nullptr);

	/** 광원 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CLight*, Light, m_pLight, nullptr);

	/** 카메라 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CCamera*, Camera, m_pCamera, nullptr);

	/** 팩토리 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(IDXGIFactory*, Factory, m_pFactory, nullptr);

	/** 스왑 체인 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(IDXGISwapChain*, SwapChain, m_pSwapChain, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10Device*, Device, m_pDevice, nullptr);

	/** 렌더 타겟 뷰 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10RenderTargetView*, View_RT, m_pView_RT, nullptr);

	/** 깊이 스텐실 뷰 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10DepthStencilView*, View_DS, m_pView_DS, nullptr);

	/** 폰트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Font*, XFont, m_pXFont, nullptr);

	/** 스프라이트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Sprite*, XSprite, m_pXSprite, nullptr);

	/** Direct 3D 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3D9, D3D, m_pD3D, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3DDEVICE9, Device9, m_pDevice9, nullptr);

public:			// public 함수

	/** 생성자 */
	CApp_D3D(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	virtual ~CApp_D3D(void);

	/** 초기화 */
	virtual void Init(void) override;

	/** 광원 상태를 갱신한다 */
	virtual void UpdateState_Light(void);

	/** 카메라 상태를 갱신한다 */
	virtual void UpdateState_Camera(void);

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

	/** 씬을 변경한다 */
	virtual void SetScene(CScene* a_pScene);

protected:			// protected 팩토리 함수

	/** 씬을 생성한다 */
	virtual CScene* CreateScene(void);

	/** 광원을 생성한다 */
	virtual CLight* CreateLight(void);

	/** 카메라를 생성한다 */
	virtual CCamera* CreateCamera(void);

	/** 팩토리를 생성한다 */
	virtual IDXGIFactory* CreateFactory(void);

	/** 스왑 체인을 생성한다 */
	virtual IDXGISwapChain* CreateSwapChain(void);

	/** 디바이스를 생성한다 */
	virtual ID3D10Device* CreateDevice(void);

	/** 렌더 타겟 뷰를 생성한다 */
	virtual ID3D10RenderTargetView* CreateView_RT(void);

	/** 깊이 스텐실 뷰를 생성한다 */
	virtual ID3D10DepthStencilView* CreateView_DS(void);

	/** 폰트를 생성한다 */
	virtual ID3DX10Font* CreateXFont(void);

	/** 스프라이트를 생성한닫 */
	virtual ID3DX10Sprite* CreateXSprite(void);

	/** Direct 3D 을 생성한다 */
	virtual LPDIRECT3D9 CreateD3D(void);

	/** 디바이스 9 를 생성한다 */
	virtual LPDIRECT3DDEVICE9 CreateDevice9(void);

private:			// private 함수

	/** 화면을 출력한다 */
	virtual void Present(HDC a_hSrcDC, HDC a_hDestDC) override;

private:			// private 변수

	std::string m_oStr_DebugInfo = STR_EMPTY;
	D3DPRESENT_PARAMETERS m_stParams_Present;

	CScene* m_pScene_Next = nullptr;
};
