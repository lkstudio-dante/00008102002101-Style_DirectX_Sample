#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 렌더링 인터페이스
 */
class IRenderable
{
public:			// public 함수

	/** 객체를 그린다 */
	virtual void Render(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void Render(LPDIRECT3DDEVICE9 a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void LateRender(LPDIRECT3DDEVICE9 a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(LPD3DXSPRITE a_pXSprite) { }
};
