#pragma once

#include "CApp_Wnd.h"
#include "../../Define/KDefine+Global.h"

class CCamera;

/**
 * Direct 3D 어플리케이션
 */
class CApp_D3D : public CApp_Wnd
{
public:

	using CApp_Wnd::OnRender;
	using CApp_Wnd::OnLateRender;

public:			// IReleasable

	/** 해제한다 */
	virtual void Release(bool a_bIsDestroy = false) override;

public:			// IUpdatable

	/** 상태를 갱신한다 */
	virtual void OnUpdate(const float a_fTimeDelta) override;

public:			// IRenderable

	/** 객체를 그린다 */
	virtual void OnRender(HDC a_hDC) final override;

	/** 객체를 그린다 */
	virtual void OnLateRender(HDC a_hDC) final override;

public:   // public 함수

	/** 배경색 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, ColorClear, m_stColorClear, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	/** 카메라 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CCamera*, Camera, m_pCamera, nullptr);

	/** 팩토리 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(IDXGIFactory*, Factory, m_pFactory, nullptr);

	/** 스왑 체인 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(IDXGISwapChain*, SwapChain, m_pSwapChain, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10Device*, Device, m_pDevice, nullptr);

	/** 렌더 타겟 뷰 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10RenderTargetView*, ViewRT, m_pViewRT, nullptr);

	/** 깊이 스텐실 뷰 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10DepthStencilView*, ViewDS, m_pViewDS, nullptr);

	/** 깊이 스텐실 상태 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10DepthStencilState*, StateDS, m_pStateDS, nullptr);

	/** 래스터라이저 상태 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10RasterizerState*, StateRasterizer, m_pStateRasterizer, nullptr);

	/** 폰트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Font*, XFont, m_pXFont, nullptr);

	/** 스프라이트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Sprite*, XSprite, m_pXSprite, nullptr);

	/** Direct 3D 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3D9, D3D9, m_pD3D9, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3DDEVICE9, Device9, m_pDevice9, nullptr);

public:			// public 함수

	/** 생성자 */
	CApp_D3D(HINSTANCE a_hInst, int a_nOptShow, const SIZE& a_rstSizeWnd);

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
	virtual void HandleMsgSize(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams) override;

protected:			// protected 접근 함수

	/** 이펙트 경로를 반환한다 */
	virtual std::string GetPathEffect(void);

protected:			// protected 팩토리 함수

	/** 카메라를 생성한다 */
	virtual CCamera* CreateCamera(void);

	/** 팩토리를 생성한다 */
	virtual IDXGIFactory* CreateFactory(void);

	/** 스완 체인을 생성한다 */
	virtual IDXGISwapChain* CreateSwapChain(void);

	/** 디바이스를 생성한다 */
	virtual ID3D10Device* CreateDevice(void);

	/** 렌더 타겟 뷰를 생성한다 */
	virtual ID3D10RenderTargetView* CreateViewRT(void);

	/** 깊이 스텐실 뷰를 생성한다 */
	virtual ID3D10DepthStencilView* CreateViewDS(void);

	/** 깊이 스텐실 상태를 생성한다 */
	virtual ID3D10DepthStencilState* CreateStateDS(void);

	/** 래스터라이저 상태를 생성한다 */
	virtual ID3D10RasterizerState* CreateStateRasterizer(void);

	/** 폰트를 생성한다 */
	virtual ID3DX10Font* CreateXFont(void);

	/** 스프라이트를 생성한다 */
	virtual ID3DX10Sprite* CreateXSprite(void);

	/** Direct 3D 9 을 생성한다 */
	virtual LPDIRECT3D9 CreateD3D9(void);

	/** 디바이스 9 을 생성한다 */
	virtual LPDIRECT3DDEVICE9 CreateDevice9(void);

private:			// private 함수

	/** 화면을 출력한다 */
	virtual void Present(HDC a_hSrcDC, HDC a_hDestDC) override;

private:			// private 변수

	std::string m_oStrDebugInfo = "";
};
