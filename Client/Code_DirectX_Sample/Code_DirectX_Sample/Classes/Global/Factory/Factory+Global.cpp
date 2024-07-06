#include "Factory+Global.h"
#include "../Function/Func+Global.h"
#include "../Utility/Base/CApp_D3D.h"
#include "../Utility/Manager/CManager_Snd.h"

namespace Factory
{
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
