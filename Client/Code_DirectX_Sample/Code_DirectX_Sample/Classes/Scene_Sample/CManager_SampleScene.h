#pragma once

#include "../Global/Define/KDefine+Global.h"
#include "../Global/Utility/Base/CApp_D3D.h"

/**
 * 샘플 씬 관리자
 */
class CManager_SampleScene : public CApp_D3D
{
public:			// public 함수

	/** 생성자 */
	CManager_SampleScene(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);
};
