#include "CManager_Snd.h"
#include "../../Factory/Factory+Global.h"
#include "../Sound/CSnd.h"

CManager_Snd::CManager_Snd(void)
	:
	m_pBGM(new CSnd())
{
	// Do Something
}

CManager_Snd::~CManager_Snd(void)
{
	SAFE_DEL(m_pBGM);

	SAFE_RELEASE(m_pDSnd);
	SAFE_RELEASE(m_pBuffer_PrimarySnd);
}

void CManager_Snd::Init(void)
{
	m_pDSnd = this->CreateDSnd();
	m_pBuffer_PrimarySnd = this->CreateBuffer_PrimarySnd();
}

void CManager_Snd::PlayBGM(const std::string& a_rPath_Snd)
{
	// 배경음 재생이 불가능 할 경우
	if(m_oPath_BGM == a_rPath_Snd)
	{
		return;
	}

	m_oPath_BGM = a_rPath_Snd;
	m_pBGM->Reset(a_rPath_Snd);

	m_pBGM->PlaySnd(true);

	this->SetIsMute_BGM(m_pBGM->GetIsMute());
	this->SetVolume_BGM(m_pBGM->GetVolume());
}

void CManager_Snd::PlaySFX(const std::string& a_rPath_Snd)
{
	auto pSnd = this->FindSFX_Playable(a_rPath_Snd);

	// 효과음 재생이 불가능 할 경우
	if(pSnd == nullptr)
	{
		return;
	}

	pSnd->PlaySnd(false);

	this->SetIsMute_SFXs(m_bIsMute_SFXs);
	this->SetVolume_SFXs(m_fVolume_SFXs);
}

void CManager_Snd::SetIsMute_BGM(bool a_bIsMute)
{
	m_pBGM->SetIsMute(a_bIsMute);
}

void CManager_Snd::SetIsMute_SFXs(bool a_bIsMute)
{
	this->EnumerateSFXs([&](CSnd* a_pSnd) -> void
	{
		a_pSnd->SetIsMute(a_bIsMute);
	});
}

void CManager_Snd::SetVolume_BGM(float a_fVolume)
{
	m_pBGM->SetVolume(a_fVolume);
}

void CManager_Snd::SetVolume_SFXs(float a_fVolume)
{
	this->EnumerateSFXs([&](CSnd* a_pSnd) -> void
	{
		a_pSnd->SetVolume(a_fVolume);
	});
}

void CManager_Snd::EnumerateSFXs(const std::function<void(CSnd*)>& a_rCallback)
{
	for(auto& rstValType : m_oMapSFXs)
	{
		for(auto pSnd : rstValType.second)
		{
			a_rCallback(pSnd);
		}
	}
}

CSnd* CManager_Snd::FindSFX_Playable(const std::string& a_rPath_Snd)
{
	// 사운드 풀이 없을 경우
	if(m_oMapSFXs.find(a_rPath_Snd) == m_oMapSFXs.end())
	{
		std::vector<CSnd*> oVectorSFXs;
		m_oMapSFXs.insert(decltype(m_oMapSFXs)::value_type(a_rPath_Snd, oVectorSFXs));
	}

	// 사운드 생성이 가능 할 경우
	if(m_oMapSFXs[a_rPath_Snd].size() < MAX_NUM_SFXS_DUPLICATE)
	{
		auto pSnd = new CSnd(a_rPath_Snd);
		m_oMapSFXs[a_rPath_Snd].push_back(pSnd);

		return pSnd;
	}

	for(auto pSnd : m_oMapSFXs[a_rPath_Snd])
	{
		// 재생 가능 할 경우
		if(!pSnd->IsPlaying())
		{
			return pSnd;
		}
	}

	return nullptr;
}

LPDIRECTSOUND8 CManager_Snd::CreateDSnd(void)
{
	LPDIRECTSOUND8 pDSnd = nullptr;
	DirectSoundCreate8(nullptr, &pDSnd, nullptr);

	return pDSnd;
}

LPDIRECTSOUNDBUFFER8 CManager_Snd::CreateBuffer_PrimarySnd(void)
{
	WAVEFORMATEX stInfo_Wave;
	ZeroMemory(&stInfo_Wave, sizeof(stInfo_Wave));

	stInfo_Wave.nChannels = 2;
	stInfo_Wave.wBitsPerSample = 16;
	stInfo_Wave.nSamplesPerSec = 44100;
	stInfo_Wave.nBlockAlign = (stInfo_Wave.wBitsPerSample / CHAR_BIT) * stInfo_Wave.nChannels;
	stInfo_Wave.nAvgBytesPerSec = stInfo_Wave.nSamplesPerSec * stInfo_Wave.nBlockAlign;
	stInfo_Wave.wFormatTag = WAVE_FORMAT_PCM;

	return Factory::CreateBuffer_Snd(0, stInfo_Wave, DSBCAPS_PRIMARYBUFFER);
}
