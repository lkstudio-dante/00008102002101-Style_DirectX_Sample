#include "CManager_Time.h"

CManager_Time::CManager_Time(void)
{
	// Do Something
}

CManager_Time::~CManager_Time(void)
{
	// Do Something
}

void CManager_Time::Update(void)
{
	auto oTime = std::chrono::system_clock::now();

	m_fTime_Delta = std::chrono::duration<float>(oTime - m_oTime_Prev).count();
	m_fTime_Running = std::chrono::duration<float>(oTime - m_oTime_Start).count();

	m_oTime_Prev = oTime;
}
