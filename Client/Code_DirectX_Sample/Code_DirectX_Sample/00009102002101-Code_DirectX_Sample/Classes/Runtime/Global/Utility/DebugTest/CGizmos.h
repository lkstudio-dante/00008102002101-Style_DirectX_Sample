#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "../Base/CObj_Debug.h"

/**
* 기즈모
*/
class CGizmos : public CObj_Debug
{
public:			// public 함수

	/** 초기화 */
	CGizmos(const std::string& a_rPath_Effect);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) override;
};
