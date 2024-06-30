#include "CManager_Time.h"

CManager_Time::CManager_Time(void)
{
	// Do Something
}

CManager_Time::~CManager_Time(void)
{
	// Do Something
}

void CManager_Time::Update(float a_fTime_Delta)
{
	auto oTime_Cur = std::chrono::system_clock::now();
	m_fTime_Delta = std::chrono::duration<float>(oTime_Cur - m_oTime_Prev).count();
	m_fTime_Running = std::chrono::duration<float>(oTime_Cur - m_oTime_Start).count();

	m_oTime_Prev = oTime_Cur;
}

void CManager_Time::Init(void)
{
	// Do Something
}
