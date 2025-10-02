#pragma once

#include "../Define/KCDefine+DirectX_Abs.h"
#include "CAccess+Cpp_Abs.h"

namespace CAccess
{
	/** 멀티 샘플 퀄리티 수준을 반환한다 */
	UINT GetLevels_MultiSampleQuality(DXGI_FORMAT a_eFmt, UINT a_nCount_Sample);

	/** 멀티 샘플 퀄리티 수준을 반환한다 */
	DWORD GetLevels_MultiSampleQuality(D3DFORMAT a_eFmt, 
		D3DMULTISAMPLE_TYPE a_eType_MultiSample);

	/** 변환 벡터를 반환한다 */
	D3DXVECTOR3 GetVec_Trans(const D3DXVECTOR3& a_rstVec,
		const D3DXMATRIXA16& a_rstMatrix, bool a_bIsCoord = true);

	/** 사원수를 반환한다 */
	D3DXQUATERNION GetQuaternion(const D3DXVECTOR3& a_rstRotate);

	/** 사원수를 반환한다 */
	D3DXQUATERNION GetQuaternion(const D3DXVECTOR3& a_rstAxis, float a_fAngle);

	/** 이동 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrix_Translate(const D3DXVECTOR3& a_rstPos);

	/** 비율 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrix_Scale(const D3DXVECTOR3& a_rstScale);

	/** 회전 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrix_Rotate(const D3DXVECTOR3& a_rstRotate);

	/** 변환 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrix_Trans(const D3DXVECTOR3& a_rstPos,
		const D3DXVECTOR3& a_rstScale, const D3DXVECTOR3& a_rstRotate);
}
