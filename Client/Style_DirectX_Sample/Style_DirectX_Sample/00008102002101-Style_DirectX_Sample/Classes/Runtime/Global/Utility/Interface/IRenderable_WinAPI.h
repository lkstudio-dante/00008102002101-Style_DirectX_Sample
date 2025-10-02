#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"

/**
* 윈도우즈 API 렌더링 인터페이스
*/
class IRenderable_WinAPI
{
public:			// public 함수

	/** 객체를 그린다 */
	virtual void Render(HDC a_hDC) { }

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) { }
};
