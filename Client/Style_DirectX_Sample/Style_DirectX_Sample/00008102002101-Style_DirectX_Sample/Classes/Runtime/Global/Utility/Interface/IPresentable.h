#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

/**
* 출력 인터페이스
*/
class IPresentable
{
public:			// public 함수

	/** 화면을 출력한다 */
	virtual void Present(void) { }
};
