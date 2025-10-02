#pragma once

/**
* 웨이브 사운드 정보
*/
struct STInfo_WaveSnd
{
	int m_nNumBytes;
	WAVEFORMATEX m_stInfo_Wave;

	LPBYTE m_pnBytes;
};
