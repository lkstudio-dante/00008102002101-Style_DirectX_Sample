#include "Factory+Global.h"
#include "../Function/Func+Global.h"
#include "../Utility/Base/CApp_D3D.h"
#include "../Utility/Manager/CManager_Snd.h"

namespace Factory
{
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlagsBind, D3D10_CPU_ACCESS_FLAG a_eFlagsCPUAccess, D3D10_USAGE a_eUsage, D3D10_SUBRESOURCE_DATA* a_pDataSubResource)
	{
		D3D10_BUFFER_DESC stDescBuffer;
		ZeroMemory(&stDescBuffer, sizeof(stDescBuffer));

		stDescBuffer.Usage = a_eUsage;
		stDescBuffer.ByteWidth = a_nNumBytes;

		stDescBuffer.BindFlags = a_eFlagsBind;
		stDescBuffer.CPUAccessFlags = a_eFlagsCPUAccess;
		stDescBuffer.MiscFlags = 0;

		ID3D10Buffer* pBuffer = nullptr;
		GET_APP_D3D()->GetDevice()->CreateBuffer(&stDescBuffer, a_pDataSubResource, &pBuffer);

		return pBuffer;
	}

	ID3D10Texture2D* CreateTexture2D(int a_nWidth,
		int a_nHeight, DXGI_FORMAT a_eFmt, D3D10_BIND_FLAG a_eFlagsBind, D3D10_CPU_ACCESS_FLAG a_eFlagsCPUAccess, D3D10_USAGE a_eUsage, D3D10_SUBRESOURCE_DATA* a_pDataSubResource)
	{
		DXGI_SWAP_CHAIN_DESC stDescSwapChain;
		GET_APP_D3D()->GetSwapChain()->GetDesc(&stDescSwapChain);

		D3D10_TEXTURE2D_DESC stDescTexture2D;
		ZeroMemory(&stDescTexture2D, sizeof(stDescTexture2D));

		stDescTexture2D.Usage = a_eUsage;
		stDescTexture2D.Width = a_nWidth;
		stDescTexture2D.Height = a_nHeight;
		stDescTexture2D.Format = a_eFmt;

		stDescTexture2D.BindFlags = a_eFlagsBind;
		stDescTexture2D.CPUAccessFlags = a_eFlagsCPUAccess;
		stDescTexture2D.MiscFlags = 0;

		stDescTexture2D.ArraySize = 1;
		stDescTexture2D.MipLevels = 1;
		stDescTexture2D.SampleDesc = stDescSwapChain.SampleDesc;

		ID3D10Texture2D* pTexture2D = nullptr;
		GET_APP_D3D()->GetDevice()->CreateTexture2D(&stDescTexture2D, a_pDataSubResource, &pTexture2D);

		return pTexture2D;
	}

	LPDIRECTSOUNDBUFFER8 CreateBufferSnd(void)
	{
		DSBUFFERDESC stDescBuffer;
		ZeroMemory(&stDescBuffer, sizeof(stDescBuffer));

		LPDIRECTSOUNDBUFFER8 pBufferSnd = nullptr;
		GET_MANAGER_SND()->GetDSnd()->CreateSoundBuffer(&stDescBuffer, (LPDIRECTSOUNDBUFFER*)&pBufferSnd, nullptr);

		return pBufferSnd;
	}
}
