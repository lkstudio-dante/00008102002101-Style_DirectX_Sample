#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

/**
* 해제 인터페이스
*/
class IReleasable
{
public:			// public 함수

	/** 리소스를 해제한다 */
	virtual void Release(void) { }

	/** 객체를 제거한다 */
	virtual void Destroy(void) { }
};
