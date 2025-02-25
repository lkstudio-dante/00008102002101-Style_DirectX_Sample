#include "CFactory+DirectX_Abs.h"
#include "../Function/CFunc+DirectX_Abs.h"

#include "../Utility/Base/CApp_D3D.h"

namespace CFactory
{
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource)
	{
		D3D10_BUFFER_DESC stDesc_Buffer;
		ZeroMemory(&stDesc_Buffer, sizeof(stDesc_Buffer));

		stDesc_Buffer.Usage = a_eUsage;
		stDesc_Buffer.ByteWidth = a_nNumBytes;

		stDesc_Buffer.MiscFlags = ::G_FLAGS_MISC_NONE;
		stDesc_Buffer.BindFlags = a_eFlags_Bind;
		stDesc_Buffer.CPUAccessFlags = a_eFlags_CPUAccess;

		ID3D10Buffer* pBuffer = nullptr;
		GET_APP_D3D()->GetDevice()->CreateBuffer(&stDesc_Buffer, a_pstData_SubResource, &pBuffer);

		return pBuffer;
	}

	ID3D10Texture2D* CreateTexture2D(int a_nWidth,
		int a_nHeight, DXGI_FORMAT a_eFmt, D3D10_BIND_FLAG a_eFlags_Bind, D3D10_USAGE a_eUsage, D3D10_CPU_ACCESS_FLAG a_eFlags_CPUAccess, D3D10_SUBRESOURCE_DATA* a_pstData_SubResource)
	{
		DXGI_SWAP_CHAIN_DESC stDesc_SwapChain;
		GET_APP_D3D()->GetSwapChain()->GetDesc(&stDesc_SwapChain);

		D3D10_TEXTURE2D_DESC stDesc_Texture2D;
		ZeroMemory(&stDesc_Texture2D, sizeof(stDesc_Texture2D));

		stDesc_Texture2D.Usage = a_eUsage;
		stDesc_Texture2D.SampleDesc = stDesc_SwapChain.SampleDesc;

		stDesc_Texture2D.Width = a_nWidth;
		stDesc_Texture2D.Height = a_nHeight;
		stDesc_Texture2D.Format = a_eFmt;

		stDesc_Texture2D.MipLevels = 1;
		stDesc_Texture2D.ArraySize = 1;

		stDesc_Texture2D.MiscFlags = ::G_FLAGS_MISC_NONE;
		stDesc_Texture2D.BindFlags = a_eFlags_Bind;
		stDesc_Texture2D.CPUAccessFlags = a_eFlags_CPUAccess;

		ID3D10Texture2D* pTexture2D = nullptr;
		GET_APP_D3D()->GetDevice()->CreateTexture2D(&stDesc_Texture2D, a_pstData_SubResource, &pTexture2D);

		return pTexture2D;
	}
}
