#include "Factory+Global.h"
#include "../Function/Func+Global.h"
#include "../Utility/Base/CApp_D3D.h"
#include "../Utility/Manager/CManager_Snd.h"

namespace Factory
{
	ID3D10Buffer* CreateBuffer(int a_nNumBytes,
		D3D10_BIND_FLAG a_eFlagsBind, D3D10_CPU_ACCESS_FLAG a_eFlagsCPUAccess, D3D10_USAGE a_eUsage, D3D10_SUBRESOURCE_DATA* a_pDataSubResource)
	{
		D3D10_BUFFER_DESC stDesc_Buffer;
		ZeroMemory(&stDesc_Buffer, sizeof(stDesc_Buffer));

		stDesc_Buffer.Usage = a_eUsage;
		stDesc_Buffer.ByteWidth = a_nNumBytes;

		stDesc_Buffer.BindFlags = a_eFlagsBind;
		stDesc_Buffer.CPUAccessFlags = a_eFlagsCPUAccess;
		stDesc_Buffer.MiscFlags = 0;

		ID3D10Buffer* pBuffer = nullptr;
		GET_APP_D3D()->GetDevice()->CreateBuffer(&stDesc_Buffer, a_pDataSubResource, &pBuffer);

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

	LPDIRECTSOUNDBUFFER8 CreateBuffer_Snd(int a_nNumBytes, const WAVEFORMATEX& a_rstInfo_Wave, DWORD a_nFlags)
	{
		DSBUFFERDESC stDesc_Buffer;
		ZeroMemory(&stDesc_Buffer, sizeof(stDesc_Buffer));

		stDesc_Buffer.dwSize = sizeof(stDesc_Buffer);
		stDesc_Buffer.dwBufferBytes = a_nNumBytes;
		stDesc_Buffer.lpwfxFormat = (LPWAVEFORMATEX)&a_rstInfo_Wave;
		stDesc_Buffer.dwFlags = a_nFlags;

		LPDIRECTSOUNDBUFFER8 pBuffer_Snd = nullptr;

		GET_MANAGER_SND()->GetDSnd()->CreateSoundBuffer(&stDesc_Buffer,
			(LPDIRECTSOUNDBUFFER*)&pBuffer_Snd, nullptr);

		return pBuffer_Snd;
	}
}
