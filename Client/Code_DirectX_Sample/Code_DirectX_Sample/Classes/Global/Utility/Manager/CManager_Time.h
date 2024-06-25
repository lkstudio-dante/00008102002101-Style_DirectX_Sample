#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IUpdateable.h"

/**
 * 시간 관리자
 */
class CManager_Time : public virtual IUpdateable
{
public:			// IUpdateable

	/** 상태를 갱신한다 */
	virtual void OnUpdate(const float a_fTimeDelta) override;

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Time);

	/** 초기화 */
	virtual void Init(void);

	/** 시간 간격 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(float, TimeDelta, m_fTimeDelta, 0.0f);

	/** 구동 시간 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(float, TimeRunning, m_fTimeRunning, 0.0f);

private:			// 변수

	std::chrono::system_clock::time_point m_oTimePrev = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point m_oTimeStart = std::chrono::system_clock::now();
};
