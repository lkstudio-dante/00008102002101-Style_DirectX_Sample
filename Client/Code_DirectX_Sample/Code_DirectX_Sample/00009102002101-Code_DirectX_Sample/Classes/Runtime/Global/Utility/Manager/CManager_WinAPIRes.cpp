#include "CManager_WinAPIRes.h"
#include "../../Function/CFunc+WinAPI_Abs.h"

CManager_WinAPIRes::CManager_WinAPIRes(void)
{
	// Do Something
}

CManager_WinAPIRes::~CManager_WinAPIRes(void)
{
	// Do Something
}

void CManager_WinAPIRes::Release(void)
{
	for(auto& rstKeyVal : m_oMapInfos_WaveSnd)
	{
		SAFE_FREE(rstKeyVal.second.m_pnBytes);
	}
}

STInfo_WaveSnd CManager_WinAPIRes::GetInfo_WaveSnd(const std::string& a_rKey,
	bool a_bIsCreate_Auto)
{
	// 웨이브 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_WaveSnd.find(a_rKey) == m_oMapInfos_WaveSnd.end())
	{
		auto hMMIO = mmioOpenA((LPSTR)a_rKey.c_str(), nullptr, MMIO_READ);
		assert(hMMIO != nullptr);

		STInfo_WaveSnd stInfo_WaveSnd;
		ZeroMemory(&stInfo_WaveSnd, sizeof(stInfo_WaveSnd));

		MMCKINFO stInfo_RIFF;
		ZeroMemory(&stInfo_RIFF, sizeof(stInfo_RIFF));

		stInfo_RIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hMMIO, &stInfo_RIFF, nullptr, MMIO_FINDRIFF);

		MMCKINFO stInfo_FmtChunk;
		ZeroMemory(&stInfo_FmtChunk, sizeof(stInfo_FmtChunk));

		stInfo_FmtChunk.fccType = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hMMIO, &stInfo_FmtChunk, &stInfo_RIFF, MMIO_FINDCHUNK);

		mmioRead(hMMIO,
			(LPSTR)&stInfo_WaveSnd.m_stInfo_Wave, sizeof(stInfo_WaveSnd.m_stInfo_Wave));

		mmioAscend(hMMIO, &stInfo_FmtChunk, 0);

		MMCKINFO stInfo_DataChunk;
		ZeroMemory(&stInfo_DataChunk, sizeof(stInfo_DataChunk));

		stInfo_DataChunk.fccType = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hMMIO, &stInfo_DataChunk, &stInfo_RIFF, MMIO_FINDCHUNK);

		stInfo_WaveSnd.m_pnBytes = (LPBYTE)malloc(stInfo_WaveSnd.m_nNumBytes);
		stInfo_WaveSnd.m_nNumBytes = stInfo_DataChunk.cksize;

		mmioRead(hMMIO,
			(LPSTR)stInfo_WaveSnd.m_pnBytes, stInfo_WaveSnd.m_nNumBytes);

		mmioClose(hMMIO, 0);
		CFunc::InsertVal(m_oMapInfos_WaveSnd, a_rKey, stInfo_WaveSnd);
	}

	return m_oMapInfos_WaveSnd[a_rKey];
}
