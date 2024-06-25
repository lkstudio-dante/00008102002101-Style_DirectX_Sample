#include "CManager_Snd.h"

CManager_Snd::CManager_Snd(void)
{
	// Do Something
}

CManager_Snd::~CManager_Snd(void)
{
	SAFE_RELEASE(m_pDSnd);
	SAFE_RELEASE(m_pBufferPrimarySnd);
}

void CManager_Snd::Init(void)
{
	m_pDSnd = this->CreateDSnd();
	m_pBufferPrimarySnd = this->CreateBufferPrimarySnd();
}

LPDIRECTSOUND8 CManager_Snd::CreateDSnd(void)
{
	LPDIRECTSOUND8 pDSnd = nullptr;
	DirectSoundCreate8(nullptr, &pDSnd, nullptr);

	return pDSnd;
}

LPDIRECTSOUNDBUFFER8 CManager_Snd::CreateBufferPrimarySnd(void)
{
	DSBUFFERDESC stDescBuffer;
	ZeroMemory(&stDescBuffer, sizeof(stDescBuffer));

	LPDIRECTSOUNDBUFFER8 pSBuffer = nullptr;
	m_pDSnd->CreateSoundBuffer(&stDescBuffer, (LPDIRECTSOUNDBUFFER*)&pSBuffer, nullptr);

	return pSBuffer;
}
