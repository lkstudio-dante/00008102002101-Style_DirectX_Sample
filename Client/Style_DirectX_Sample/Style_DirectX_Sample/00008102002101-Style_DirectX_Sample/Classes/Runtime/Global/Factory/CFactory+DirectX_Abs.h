#pragma once

#include "../Define/KCDefine+DirectX_Abs.h"

#include "CFactory+Cpp_Abs.h"
#include "CFactory+WinAPI_Abs.h"

namespace CFactory
{
	/** 버퍼를 생성한다 */
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess = ::G_FLAGS_CPU_ACCESS_NONE, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource = nullptr);

	/** 텍스처 2D 를 생성한다 */
	ID3D10Texture2D* CreateTexture2D(int a_nWidth,
		int a_nHeight, DXGI_FORMAT a_eFmt, D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage = D3D10_USAGE_DEFAULT, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess = ::G_FLAGS_CPU_ACCESS_NONE, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource = nullptr);
}
