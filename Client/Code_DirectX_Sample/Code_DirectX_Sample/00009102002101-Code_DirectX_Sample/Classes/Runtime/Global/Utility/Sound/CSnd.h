#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "../Base/CObj.h"

/**
* 사운드
*/
class CSnd : public CObj
{
public:			// public 함수

	/** 생성자 */
	CSnd(void);

	/** 생성자 */
	CSnd(const std::string& a_rPath_Snd);

	/** 사운드를 리셋한다 */
	virtual void Reset(const std::string& a_rPath_Snd);

	/** 플레이 여부를 반환한다 */
	virtual bool IsPlaying(void) const;

	/** 사운드를 재생한다 */
	virtual void PlaySnd(bool a_bIsLoop);

	/** 사운드를 중지한다 */
	virtual void StopSnd(void);

	/** 음소거 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(bool, IsMute, m_bIsMute, false);

	/** 볼륨 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(float, Volume, m_fVolume, 1.0f);

	/** 사운드 버퍼 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUNDBUFFER8, Buffer_Snd, m_pBuffer_Snd, nullptr);

public:			// public 접근 함수

	/** 음소거 여부를 변경한다 */
	void SetIsMute(bool a_bIsMute);

	/** 볼륨을 변경한다 */
	void SetVolume(float a_fVolume);
};
