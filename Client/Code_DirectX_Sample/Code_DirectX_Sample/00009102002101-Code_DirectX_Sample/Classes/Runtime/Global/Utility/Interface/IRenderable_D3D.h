#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"

/**
* Direct 3D 렌더링 인터페이스
*/
class IRenderable_D3D
{
public:			// public 함수

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(ID3D10Device* a_pDevice) { }

	/** 객체를 그린다 */
	virtual void LateRender(ID3DX10Sprite* a_pXSprite) { }
};
