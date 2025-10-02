#pragma once

#include "../Define/KCDefine+WinAPI_Abs.h"
#include "CFactory+Cpp_Abs.h"

namespace CFactory
{
	/** 입력 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDevice_Input(const GUID& a_rstGUID,
		LPCDIDATAFORMAT a_pstFmt_Data, DWORD a_nCoLevel);

	/** 사운드 버퍼를 생성한다 */
	LPDIRECTSOUNDBUFFER8 CreateBuffer_Snd(int a_nNumBytes,
		const WAVEFORMATEX& a_rstInfo_Wave, DWORD a_nFlags);
}
