#include "CManager_Time.h"

CManager_Time::CManager_Time(void)
{
	// Do Something
}

CManager_Time::~CManager_Time(void)
{
	// Do Something
}

void CManager_Time::OnUpdate(const float a_fTimeDelta)
{
	auto oTimeCur = std::chrono::system_clock::now();
	m_fTimeDelta = std::chrono::duration<float>(oTimeCur - m_oTimePrev).count();
	m_fTimeRunning = std::chrono::duration<float>(oTimeCur - m_oTimeStart).count();

	m_oTimePrev = oTimeCur;
}

void CManager_Time::Init(void)
{
	// Do Something
}
