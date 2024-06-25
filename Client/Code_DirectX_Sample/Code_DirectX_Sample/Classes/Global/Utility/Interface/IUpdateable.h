#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 상태 갱신 인터페이스
 */
class IUpdateable
{
public:			// public 함수

	/** 상태를 갱신한다 */
	virtual void OnUpdate(const float a_fTimeDelta) { }

	/** 상태를 갱신한다 */
	virtual void OnLateUpdate(const float a_fTimeDelta) { }
};
