#pragma once

#include "../Define/KDefine+Global.h"

namespace Factory
{
	/** 버퍼를 생성한다 */
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlagsBind, D3D10_CPU_ACCESS_FLAG a_eFlagsCPUAccess, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_SUBRESOURCE_DATA* a_pDataSubResource = nullptr);

	/** 2 차원 버퍼를 생성한다 */
	ID3D10Texture2D* CreateTexture2D(int a_nWidth,
		int a_nHeight, DXGI_FORMAT a_eFmt, D3D10_BIND_FLAG a_eFlagsBind, D3D10_CPU_ACCESS_FLAG a_eFlagsCPUAccess, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_SUBRESOURCE_DATA* a_pDataSubResource = nullptr);

	/** 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBufferSnd(void);
}
