#include "CSnd.h"
#include "../../Factory/Factory+Global.h"
#include "../Manager/CManager_Res.h"

CSnd::CSnd(void)
{
	// Do Something
}

CSnd::CSnd(const std::string& a_rPath_Snd)
{
	this->Reset(a_rPath_Snd);
}

void CSnd::Reset(const std::string& a_rPath_Snd)
{
	auto stInfo_WaveSnd = GET_MANAGER_RES()->GetInfo_WaveSnd(a_rPath_Snd);
	SAFE_RELEASE(m_pBuffer_Snd);

	m_pBuffer_Snd = Factory::CreateBuffer_Snd(stInfo_WaveSnd.m_nNumBytes,
		stInfo_WaveSnd.m_stInfo_Wave, DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME);

	int nNumBytes = 0;
	LPVOID pvBuffer = nullptr;

	// 버퍼 설정이 가능 할 경우
	if(SUCCEEDED(m_pBuffer_Snd->Lock(0, 0, &pvBuffer, (LPDWORD)&nNumBytes, 0, 0, 0)))
	{
		memcpy(pvBuffer, stInfo_WaveSnd.m_pnBytes, stInfo_WaveSnd.m_nNumBytes);
		m_pBuffer_Snd->Unlock(pvBuffer, nNumBytes, nullptr, 0);
	}
}

bool CSnd::IsPlaying(void) const
{
	DWORD nState = 0;
	m_pBuffer_Snd->GetStatus(&nState);

	return nState & DSBSTATUS_PLAYING;
}

void CSnd::PlaySnd(bool a_bIsLoop)
{
	m_pBuffer_Snd->Play(0, 0, a_bIsLoop ? DSBPLAY_LOOPING : 0);
}

void CSnd::StopSnd(void)
{
	m_pBuffer_Snd->Stop();
}

void CSnd::SetIsMute(bool a_bIsMute)
{
	m_bIsMute = a_bIsMute;
	this->SetVolume(m_fVolume);
}

void CSnd::SetVolume(float a_fVolume)
{
	m_fVolume = min(1.0f, max(0.0f, a_fVolume));
	m_pBuffer_Snd->SetVolume(m_bIsMute ? DSBVOLUME_MIN : (int)((m_fVolume - 1.0f) * -DSBVOLUME_MIN));
}
