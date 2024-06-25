#pragma once

#include "../Define/KDefine+Global.h"

namespace Func
{
	/** 멀티 샘플 퀄리티 수준을 반환한다 */
	UINT GetLevelsMultiSampleQuality(DXGI_FORMAT a_eFmt, int a_nNumSamples);

	/** 멀티 샘플 퀄리티 수준을 반환한다 */
	DWORD GetLevelsMultiSampleQuality(D3DFORMAT a_eFmt, D3DMULTISAMPLE_TYPE a_eTypeMultiSample);
}
