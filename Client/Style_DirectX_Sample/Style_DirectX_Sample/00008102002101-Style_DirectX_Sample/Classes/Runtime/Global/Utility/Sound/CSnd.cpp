#include "CSnd.h"
#include "../../Function/CFunc+C_Abs.h"
#include "../../Factory/CFactory+WinAPI_Abs.h"

#include "../Manager/CManager_WinAPIRes.h"

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
	auto stInfo_WaveSnd = GET_MANAGER_WIN_API_RES()->GetInfo_WaveSnd(a_rPath_Snd);
	SAFE_RELEASE(m_pBuffer_Snd);

	m_pBuffer_Snd = CFactory::CreateBuffer_Snd(stInfo_WaveSnd.m_nNumBytes,
		stInfo_WaveSnd.m_stInfo_Wave, DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME);

	int nNumBytes = 0;
	LPVOID pvBuffer = nullptr;

	// 버퍼 설정이 가능 할 경우
	if(SUCCEEDED(m_pBuffer_Snd->Lock(0, 0, &pvBuffer, (LPDWORD)&nNumBytes, 0, 0, 0)))
	{
		CopyMemory(pvBuffer, stInfo_WaveSnd.m_pnBytes, stInfo_WaveSnd.m_nNumBytes);
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
	m_fVolume = MIN(1.0f, MAX(0.0f, a_fVolume));

	m_pBuffer_Snd->SetVolume(m_bIsMute ? 
		DSBVOLUME_MIN : (int)((1.0f - m_fVolume) * DSBVOLUME_MIN));
}
