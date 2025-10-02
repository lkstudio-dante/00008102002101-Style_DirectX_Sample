#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

/**
* 상태 갱신 인터페이스
*/
class IUpdateable
{
public:			// public 함수

	/** 상태를 갱신한다 */
	virtual void Update(void) { }

	/** 상태를 갱신한다 */
	virtual void Update(float a_fTime_Delta) { }

	/** 상태를 갱신한다 */
	virtual void LateUpdate(void) { }

	/** 상태를 갱신한다 */
	virtual void LateUpdate(float a_fTime_Delta) { }
};
