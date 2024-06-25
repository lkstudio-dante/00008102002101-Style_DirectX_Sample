#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 렌더링 인터페이스
 */
class IRenderable
{
public:			// public 함수

	/** 객체를 그린다 */
	virtual void OnRender(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void OnRender(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void OnLateRender(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3DX10Sprite* a_pXSprite) { }
};
