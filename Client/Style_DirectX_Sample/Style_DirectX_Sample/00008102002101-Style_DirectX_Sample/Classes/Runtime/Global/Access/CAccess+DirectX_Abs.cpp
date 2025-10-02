#include "CAccess+DirectX_Abs.h"
#include "../Utility/Base/CApp_D3D.h"

namespace CAccess
{
	UINT GetLevels_MultiSampleQuality(DXGI_FORMAT a_eFmt, UINT a_nCount_Sample)
	{
		UINT nNumLevel_Qualitys = 0;

		GET_APP_D3D()->GetDevice()->CheckMultisampleQualityLevels(a_eFmt, 
			a_nCount_Sample, &nNumLevel_Qualitys);

		return nNumLevel_Qualitys;
	}

	DWORD GetLevels_MultiSampleQuality(D3DFORMAT a_eFmt, 
		D3DMULTISAMPLE_TYPE a_eType_MultiSample)
	{
		D3DCAPS9 stCaps_Device;
		ZeroMemory(&stCaps_Device, sizeof(stCaps_Device));

		GET_APP_D3D()->GetD3D9()->GetDeviceCaps(D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_NULLREF, &stCaps_Device);

		DWORD nNumLevel_Qualitys = 0;

		GET_APP_D3D()->GetD3D9()->CheckDeviceMultiSampleType(stCaps_Device.AdapterOrdinal,
			stCaps_Device.DeviceType, a_eFmt, true, a_eType_MultiSample, &nNumLevel_Qualitys);

		return nNumLevel_Qualitys;
	}

	D3DXVECTOR3 GetVec_Trans(const D3DXVECTOR3& a_rstVec, 
		const D3DXMATRIXA16& a_rstMatrix, bool a_bIsCoord)
	{
		D3DXVECTOR3 stVec;

		return a_bIsCoord ?
			*D3DXVec3TransformCoord(&stVec, &a_rstVec, &a_rstMatrix) : *D3DXVec3TransformNormal(&stVec, &a_rstVec, &a_rstMatrix);
	}

	D3DXQUATERNION GetQuaternion(const D3DXVECTOR3& a_rstRotate)
	{
		D3DXQUATERNION stQuaternion;

		return *D3DXQuaternionRotationYawPitchRoll(&stQuaternion,
			D3DXToRadian(a_rstRotate.y), D3DXToRadian(a_rstRotate.x), D3DXToRadian(a_rstRotate.z));
	}

	D3DXQUATERNION GetQuaternion(const D3DXVECTOR3& a_rstAxis, float a_fAngle)
	{
		D3DXQUATERNION stQuaternion;
		return *D3DXQuaternionRotationAxis(&stQuaternion, &a_rstAxis, D3DXToRadian(a_fAngle));
	}

	D3DXMATRIXA16 GetMatrix_Translate(const D3DXVECTOR3& a_rstPos)
	{
		D3DXMATRIXA16 stMatrix_Translate;
		return *D3DXMatrixTranslation(&stMatrix_Translate, a_rstPos.x, a_rstPos.y, a_rstPos.z);
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
		return CAccess::GetMatrix_Scale(a_rstScale) *
			CAccess::GetMatrix_Rotate(a_rstRotate) * CAccess::GetMatrix_Translate(a_rstPos);
	}
}
