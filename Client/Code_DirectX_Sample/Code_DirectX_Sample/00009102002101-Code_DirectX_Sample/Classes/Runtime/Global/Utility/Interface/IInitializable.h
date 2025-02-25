#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

/**
* 초기화 인터페이스
*/
class IInitializable
{
public:			// public 함수

	/** 초기화 */
	virtual void Init(void) { }

	/** 초기화 */
	virtual void LateInit(void) { }
};
