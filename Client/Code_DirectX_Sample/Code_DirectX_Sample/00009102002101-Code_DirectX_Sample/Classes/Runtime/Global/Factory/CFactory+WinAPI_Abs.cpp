#include "CFactory+WinAPI_Abs.h"
#include "../Utility/Manager/CManager_Input.h"
#include "../Utility/Manager/CManager_Snd.h"
#include "../Utility/Base/CApp_WinAPI.h"

namespace CFactory
{
	LPDIRECTINPUTDEVICE8 CreateDevice_Input(const GUID& a_rstGUID,
		LPCDIDATAFORMAT a_pstFmt_Data, DWORD a_nCoLevel)
	{
		LPDIRECTINPUTDEVICE8 pDevice_Input = nullptr;
		GET_MANAGER_INPUT()->GetDInput()->CreateDevice(a_rstGUID, &pDevice_Input, nullptr);

		pDevice_Input->SetDataFormat(a_pstFmt_Data);
		pDevice_Input->SetCooperativeLevel(GET_HANDLE_WND(), a_nCoLevel);
		pDevice_Input->Acquire();

		return pDevice_Input;
	}

	LPDIRECTSOUNDBUFFER8 CreateBuffer_Snd(int a_nNumBytes,
		const WAVEFORMATEX& a_rstInfo_Wave, DWORD a_nFlags)
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
