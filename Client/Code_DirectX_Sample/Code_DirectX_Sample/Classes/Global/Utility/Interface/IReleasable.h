#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 해제 인터페이스
 */
class IReleasable
{
public:			// public 함수

	/** 해제한다 */
	virtual void Release(bool a_bIsDestroy = false) { }
};
