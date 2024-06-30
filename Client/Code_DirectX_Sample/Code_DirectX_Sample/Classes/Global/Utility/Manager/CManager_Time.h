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
	virtual void Update(float a_fTime_Delta) override;

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Time);

	/** 초기화 */
	virtual void Init(void);

	/** 시간 간격 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(float, Time_Delta, m_fTime_Delta, 0.0f);

	/** 구동 시간 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(float, Time_Running, m_fTime_Running, 0.0f);

private:			// 변수

	std::chrono::system_clock::time_point m_oTime_Prev = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point m_oTime_Start = std::chrono::system_clock::now();
};
