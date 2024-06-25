#pragma once

#include "../../Define/KDefine+Global.h"

class CSnd;

/**
 * 사운드 관리자
 */
class CManager_Snd
{
public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Snd);

	/** 초기화 */
	virtual void Init(void);

	/** Direct Sound 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUND8, DSnd, m_pDSnd, nullptr);

	/** 주 사운드 버퍼 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUNDBUFFER8, BufferPrimarySnd, m_pBufferPrimarySnd, nullptr);

private:			// private 팩토리 함수

	/** Direct Sound 를 생성한다 */
	LPDIRECTSOUND8 CreateDSnd(void);

	/** 주 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBufferPrimarySnd(void);

private:			// private 변수

	CSnd* m_pBGM = nullptr;
	std::unordered_map<std::string, std::vector<CSnd*>> m_oMapSFXs;
};
