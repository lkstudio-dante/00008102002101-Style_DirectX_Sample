#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Base/CObj.h"

/**
 * 광원
 */
class CLight : public CObj
{
public:			// public 함수

	/** 생성자 */
	CLight(void);

	/** 색상 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(D3DXCOLOR, Color, m_stColor, COLOR_WHITE)
};
