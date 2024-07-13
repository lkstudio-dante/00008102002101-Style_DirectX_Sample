#include "Access+Global.h"
#include "../Utility/Base/CApp_D3D.h"

namespace Access
{
	UINT GetLevels_MultiSampleQuality(DXGI_FORMAT a_eFmt, UINT a_nCount_Sample)
	{
		UINT nNumQualityLevels = 0;
		GET_APP_D3D()->GetDevice()->CheckMultisampleQualityLevels(a_eFmt, a_nCount_Sample, &nNumQualityLevels);

		return nNumQualityLevels;
	}

	DWORD GetLevels_MultiSampleQuality(D3DFORMAT a_eFmt, D3DMULTISAMPLE_TYPE a_eType_MultiSample)
	{
		D3DCAPS9 stCaps_Device;
		ZeroMemory(&stCaps_Device, sizeof(stCaps_Device));

		GET_APP_D3D()->GetD3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCaps_Device);
		DWORD nNumQualityLevels = 0;

		GET_APP_D3D()->GetD3D()->CheckDeviceMultiSampleType(stCaps_Device.AdapterOrdinal,
			stCaps_Device.DeviceType, a_eFmt, true, a_eType_MultiSample, &nNumQualityLevels);

		return nNumQualityLevels;
	}

	D3DXVECTOR3 GetVec_Trans(const D3DXVECTOR3& a_rstVec, const D3DXMATRIXA16& a_rstMatrix, bool a_bIsCoord)
	{
		D3DXVECTOR3 stVec = VEC_ZERO;

		return a_bIsCoord ? 
			*D3DXVec3TransformCoord(&stVec, &a_rstVec, &a_rstMatrix) : *D3DXVec3TransformNormal(&stVec, &a_rstVec, &a_rstMatrix);
	}

	D3DXQUATERNION GetQuaternion(const D3DXVECTOR3& a_rstRotate)
	{
		D3DXQUATERNION stQuaternion;

		return *D3DXQuaternionRotationYawPitchRoll(&stQuaternion,
			D3DXToRadian(a_rstRotate.y), D3DXToRadian(a_rstRotate.x), D3DXToRadian(a_rstRotate.z));
	}

	D3DXMATRIXA16 GetMatrix_Pos(const D3DXVECTOR3& a_rstPos)
	{
		D3DXMATRIXA16 stMatrix_Pos;
		return *D3DXMatrixTranslation(&stMatrix_Pos, a_rstPos.x, a_rstPos.y, a_rstPos.z);
	}

	D3DXMATRIXA16 GetMatrix_Scale(const D3DXVECTOR3& a_rstScale)
	{
		D3DXMATRIXA16 stMatrix_Scale;
		return *D3DXMatrixScaling(&stMatrix_Scale, a_rstScale.x, a_rstScale.y, a_rstScale.z);
	}

	D3DXMATRIXA16 GetMatrix_Rotate(const D3DXVECTOR3& a_rstRotate)
	{
		D3DXMATRIXA16 stMatrix_Rotate;

		return *D3DXMatrixRotationYawPitchRoll(&stMatrix_Rotate,
			D3DXToRadian(a_rstRotate.y), D3DXToRadian(a_rstRotate.x), D3DXToRadian(a_rstRotate.z));
	}

	D3DXMATRIXA16 GetMatrix_Trans(const D3DXVECTOR3& a_rstPos,
		const D3DXVECTOR3& a_rstScale, const D3DXVECTOR3& a_rstRotate)
	{
		return Access::GetMatrix_Scale(a_rstScale) * 
			Access::GetMatrix_Rotate(a_rstRotate) * Access::GetMatrix_Pos(a_rstPos);
	}
}
