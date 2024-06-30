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
	virtual void Render(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void LateRender(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(ID3DX10Sprite* a_pXSprite) { }
};
