#pragma once

#include "../Define/KDefine+Global.h"

namespace Access
{
	/** 멀티 샘플 퀄리티 수준을 반환한다 */
	DWORD GetLevels_MultiSampleQuality(D3DFORMAT a_eFmt, D3DMULTISAMPLE_TYPE a_eType_MultiSample);

	/** 변환 벡터를 반환한다 */
	D3DXVECTOR3 GetVec_Trans(const D3DXVECTOR3& a_rstVec,
		const D3DXMATRIXA16& a_rstMatrix, bool a_bIsCoord = true);

	/** 변환 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrix_Trans(const D3DXVECTOR3& a_rstPos,
		const D3DXVECTOR3& a_rstScale, const D3DXVECTOR3& a_rstRotate);
}
