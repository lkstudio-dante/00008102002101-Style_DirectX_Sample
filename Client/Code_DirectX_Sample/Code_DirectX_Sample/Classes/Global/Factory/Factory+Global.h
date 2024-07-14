#pragma once

#include "../Define/KDefine+Global.h"

namespace Factory
{
	/** 버퍼를 생성한다 */
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess = FLAGS_CPU_ACCESS_NONE, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource = nullptr);

	/** 텍스처 2D 를 생성한다 */
	ID3D10Texture2D* CreateTexture2D(int a_nWidth,
		int a_nHeight, DXGI_FORMAT a_eFmt, D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess = FLAGS_CPU_ACCESS_NONE, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource = nullptr);

	/** 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBuffer_Snd(int a_nNumBytes, const WAVEFORMATEX& a_rstInfo_Wave, DWORD a_nFlags);

	/** 객체를 생성한다 */
	template <typename TObj, typename ...ARGS>
	TObj* CreateObj(const ARGS&& ...args);
}

#include "Factory+Global.inl"
