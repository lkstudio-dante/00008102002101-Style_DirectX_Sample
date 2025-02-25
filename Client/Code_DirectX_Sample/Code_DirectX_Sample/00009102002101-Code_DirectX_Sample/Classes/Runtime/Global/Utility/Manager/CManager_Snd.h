#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "../Base/CObj.h"

class CSnd;

/**
* 사운드 관리자
*/
class CManager_Snd : public CObj
{
public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Snd);

	/** 초기화 */
	virtual void Init(void) override;

	/** 리소스를 해제한다 */
	virtual void Release(void) override;

	/** 배경음을 재생한다 */
	virtual void PlayBGM(const std::string& a_rPath_Snd);

	/** 효과음을 재생한다 */
	virtual void PlaySFX(const std::string& a_rPath_Snd);

	/** Direct Sound 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUND8, DSnd, m_pDSnd, nullptr);

	/** 주 사운드 버퍼 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUNDBUFFER8, 
		Buffer_PrimarySnd, m_pBuffer_PrimarySnd, nullptr);

public:			// public 접근 함수

	/** 배경음 음소거 여부를 변경한다 */
	virtual void SetIsMute_BGM(bool a_bIsMute);

	/** 효과음 음소거 여부를 변경한다 */
	virtual void SetIsMute_SFXs(bool a_bIsMute);

	/** 배경음 볼륨을 변경한다 */
	virtual void SetVolume_BGM(float a_fVolume);

	/** 효과음 볼륨을 변경한다 */
	virtual void SetVolume_SFXs(float a_fVolume);

private:			// private 함수

	/** 효과음을 순회한다 */
	void EnumerateSFXs(const std::function<void(CSnd*)>& a_rCallback);

	/** 효과음을 탐색한다 */
	CSnd* FindSFX_Playable(const std::string& a_rPath_Snd);

private:			// private 팩토리 함수

	/** Direct Sound 를 생성한다 */
	LPDIRECTSOUND8 CreateDSnd(void);

	/** 주 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBuffer_PrimarySnd(void);

private:			// private 변수

	bool m_bIsMute_SFXs = false;
	float m_fVolume_SFXs = 1.0f;
	std::string m_oPath_BGM = "";

	CSnd* m_pBGM = nullptr;
	std::unordered_map<std::string, std::vector<CSnd*>> m_oMapSFXs;
};
