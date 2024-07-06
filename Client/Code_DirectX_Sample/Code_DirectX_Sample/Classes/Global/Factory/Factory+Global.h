#pragma once

#include "../Define/KDefine+Global.h"

namespace Factory
{
	/** 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBuffer_Snd(int a_nNumBytes, const WAVEFORMATEX& a_rstInfo_Wave, DWORD a_nFlags);
}
