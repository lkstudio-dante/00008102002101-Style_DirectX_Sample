#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 사운드
 */
class CSnd
{
public:			// public 함수

	/** 초기화 */
	virtual void Init(const std::string& a_rPathSnd);

	/** 주 사운드 버퍼 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTSOUNDBUFFER8, BufferPrimarySnd, m_pBufferPrimarySnd, nullptr);

private:			// private 변수

	std::string m_oPathSnd = "";
};
