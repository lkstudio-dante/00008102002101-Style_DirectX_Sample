#include "Access+Global.h"
#include "../Utility/Base/CApp_D3D.h"

namespace Access
{
	DXGI_FORMAT GetFmt_InputElement(BYTE a_nType)
	{
		switch(a_nType)
		{
			case D3DDECLTYPE_FLOAT1: return DXGI_FORMAT_R32_FLOAT;
			case D3DDECLTYPE_FLOAT2: return DXGI_FORMAT_R32G32_FLOAT;
			case D3DDECLTYPE_FLOAT3: return DXGI_FORMAT_R32G32B32_FLOAT;
			case D3DDECLTYPE_FLOAT4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	const char* GetName_Semantic(BYTE a_nUsage)
	{
		switch(a_nUsage)
		{
			case D3DDECLUSAGE_POSITION: return "POSITION";
			case D3DDECLUSAGE_COLOR: return "COLOR";
			case D3DDECLUSAGE_NORMAL: return "NORMAL";
			case D3DDECLUSAGE_TANGENT: return "TANGENT";
			case D3DDECLUSAGE_BINORMAL: return "BINORMAL";
			case D3DDECLUSAGE_TEXCOORD: return "TEXCOORD";
			case D3DDECLUSAGE_BLENDWEIGHT: return "BLENDWEIGHT";
		}

		return "";
	}

	UINT GetLevels_MultiSampleQuality(DXGI_FORMAT a_eFmt, int a_nNumSamples)
	{
		UINT nNumQualityLevels = 0;
		GET_APP_D3D()->GetDevice()->CheckMultisampleQualityLevels(a_eFmt, a_nNumSamples, &nNumQualityLevels);

		return nNumQualityLevels;
	}

	DWORD GetLevels_MultiSampleQuality(D3DFORMAT a_eFmt, D3DMULTISAMPLE_TYPE a_eTypeMultiSample)
	{
		D3DCAPS9 stCapsDevice;
		ZeroMemory(&stCapsDevice, sizeof(stCapsDevice));

		GET_APP_D3D()->GetD3D9()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCapsDevice);
		DWORD nNumQualityLevels = 0;

		GET_APP_D3D()->GetD3D9()->CheckDeviceMultiSampleType(stCapsDevice.AdapterOrdinal,
			stCapsDevice.DeviceType, a_eFmt, true, a_eTypeMultiSample, &nNumQualityLevels);

		return nNumQualityLevels;
	}

	D3DXVECTOR3 GetVec_Trans(const D3DXVECTOR3& a_rstVec, const D3DXMATRIXA16& a_rstMatrix, bool a_bIsCoord)
	{
		D3DXVECTOR3 stVec(0.0f, 0.0f, 0.0f);

		// 위치 일 경우
		if(a_bIsCoord)
		{
			D3DXVec3TransformCoord(&stVec, &a_rstVec, &a_rstMatrix);
		}
		else
		{
			D3DXVec3TransformNormal(&stVec, &a_rstVec, &a_rstMatrix);
		}

		return *D3DXVec3Normalize(&stVec, &stVec);
	}

	D3DXMATRIXA16 GetMatrix_Trans(const D3DXVECTOR3& a_rstPos,
		const D3DXVECTOR3& a_rstScale, const D3DXVECTOR3& a_rstRotate)
	{
		D3DXMATRIXA16 stMatrix_Pos;
		D3DXMatrixTranslation(&stMatrix_Pos, a_rstPos.x, a_rstPos.y, a_rstPos.z);

		D3DXMATRIXA16 stMatrix_Scale;
		D3DXMatrixScaling(&stMatrix_Scale, a_rstScale.x, a_rstScale.y, a_rstScale.z);

		D3DXMATRIXA16 stMatrix_Rotate;
		D3DXMatrixRotationYawPitchRoll(&stMatrix_Rotate, a_rstRotate.y, a_rstRotate.x, a_rstRotate.z);

		return stMatrix_Scale * stMatrix_Rotate * stMatrix_Pos;
	}
}
