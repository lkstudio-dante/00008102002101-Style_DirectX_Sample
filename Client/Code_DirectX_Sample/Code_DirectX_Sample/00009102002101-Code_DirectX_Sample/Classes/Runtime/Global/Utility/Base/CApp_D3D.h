#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "CApp_WinAPI.h"

#include "../Interface/IRenderable_D3D.h"

class CScene_D3D;

/**
* Direct 3D 어플리케이션
*/
class CApp_D3D : public CApp_WinAPI, public virtual IRenderable_D3D
{
public:   // public 함수

	/** 생성자 */
	CApp_D3D(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	virtual ~CApp_D3D(void) = 0;

	/** 초기화 */
	virtual void Init(void) override;

	/** 초기호 */
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
	virtual void Render(void) final override;

	/** 객체를 그린다 */
	virtual void LateRender(void) final override;

	/** 배경색 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, 
		Color_Clear, m_stColor_Clear, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

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

	/** 깊이 스텐실 상태 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10DepthStencilState*, State_DS, m_pState_DS, nullptr);

	/** 폰트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Font*, XFont, m_pXFont, nullptr);

	/** 스프라이트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Sprite*, XSprite, m_pXSprite, nullptr);

	/** Direct 3D 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3D9, D3D9, m_pD3D9, nullptr);

	/** 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECT3DDEVICE9, Device9, m_pDevice9, nullptr);

protected:			// protected 함수

	/** 디바이스를 리셋한다 */
	virtual void ResetDevice(void);

	/** 카메라를 리셋한다 */
	virtual void ResetCamera(void);

	/** 뷰 포트를 리셋한다 */
	virtual void ResetViewport(void);

	/** 크기 메세지를 처리한다 */
	virtual void HandleMsg_Size(HWND a_hWnd, WPARAM a_wParams, LPARAM a_lParams) override;

protected:			// protected 접근 함수

	/** 이펙트 경로를 반환한다 */
	virtual std::string GetPath_Effect(void);

protected:			// protected 팩토리 함수

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

	/** 깊이 스텐실 상태를 생성한다 */
	virtual ID3D10DepthStencilState* CreateState_DS(void);

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
	virtual void Present(void) override;

private:			// private 변수

	std::string m_oStr_DebugInfo = "";
	D3DPRESENT_PARAMETERS m_stParams_Present;
};
