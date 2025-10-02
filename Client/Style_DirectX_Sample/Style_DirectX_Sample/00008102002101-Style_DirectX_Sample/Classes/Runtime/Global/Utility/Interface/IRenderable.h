#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

/**
* 렌더링 인터페이스
*/
class IRenderable
{
public:			// public 함수

	/** 객체를 그린다 */
	virtual void Render(void) { }

	/** 객체를 그린다 */
	virtual void LateRender(void) { }
};
