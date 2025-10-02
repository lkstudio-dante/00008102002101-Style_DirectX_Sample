#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "../Base/CObj_D3D.h"

/**
* 광원
*/
class CLight : public CObj_D3D
{
public:			// public 함수

	/** 생성자 */
	CLight(void);

	/** 색상 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, Color, m_stColor, ::G_COLOR_WHITE)
};
