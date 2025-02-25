#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "../Base/CObj.h"

/**
* 윈도우즈 API 리소스 관리자
*/
class CManager_WinAPIRes : public CObj
{
public:			// IReleasable

	/** 리소스를 해제한다 */
	virtual void Release(void) override;

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_WinAPIRes);

	/** 웨이브 사운드 정보 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, STInfo_WaveSnd),
		Infos_WaveSnd, m_oMapInfos_WaveSnd);

public:			// public 접근 함수

	/** 웨이브 사운드 정보를 반환한다 */
	STInfo_WaveSnd GetInfo_WaveSnd(const std::string& a_rKey,
		bool a_bIsCreate_Auto = true);
};
