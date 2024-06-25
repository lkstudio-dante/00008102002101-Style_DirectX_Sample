#include "Func+Global.h"
#include "../Utility/Base/CApp_D3D.h"

namespace Func
{
	UINT GetLevelsMultiSampleQuality(DXGI_FORMAT a_eFmt, int a_nNumSamples)
	{
		UINT nNumQualityLevels = 0;
		GET_APP_D3D()->GetDevice()->CheckMultisampleQualityLevels(a_eFmt, a_nNumSamples, &nNumQualityLevels);

		return nNumQualityLevels;
	}

	DWORD GetLevelsMultiSampleQuality(D3DFORMAT a_eFmt, D3DMULTISAMPLE_TYPE a_eTypeMultiSample)
	{
		D3DCAPS9 stCapsDevice;
		ZeroMemory(&stCapsDevice, sizeof(stCapsDevice));

		GET_APP_D3D()->GetD3D9()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, &stCapsDevice);
		DWORD nNumQualityLevels = 0;

		GET_APP_D3D()->GetD3D9()->CheckDeviceMultiSampleType(stCapsDevice.AdapterOrdinal,
			stCapsDevice.DeviceType, a_eFmt, true, a_eTypeMultiSample, &nNumQualityLevels);

		return nNumQualityLevels;
	}
}
