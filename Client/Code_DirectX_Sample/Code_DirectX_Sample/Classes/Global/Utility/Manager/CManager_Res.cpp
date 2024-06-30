#include "CManager_Res.h"
#include "../Base/CApp_D3D.h"

/** 리소스를 제거한다 */
template <typename T>
static void ReleaseResources(std::vector<T>& a_rVectorResources)
{
	for(auto pRes : a_rVectorResources)
	{
		SAFE_RELEASE(pRes);
	}
}

/** 리소스를 제거한다 */
template <typename K, typename V>
static void ReleaseResources(std::unordered_map<K, V>& a_rMapResources)
{
	for(auto& rstValType : a_rMapResources)
	{
		SAFE_RELEASE(rstValType.second);
	}
}

CManager_Res::CManager_Res(void)
{
	// Do Something
}

CManager_Res::~CManager_Res(void)
{
	this->Release(true);
}

void CManager_Res::Release(bool a_bIsDestroy)
{
	::ReleaseResources(m_oMapEffects);
	::ReleaseResources(m_oMapViews_SR);

	for(auto& rstValType : m_oMapInfos_Mesh)
	{
		SAFE_RELEASE(rstValType.second.m_pMesh);
		::ReleaseResources(rstValType.second.m_oVectorViews_SR);
	}

	for(auto& rstValType : m_oMapInfos_WaveSnd)
	{
		SAFE_FREE(rstValType.second.m_pnBytes);
	}
}

void CManager_Res::Init(void)
{
	// Do Something
}

STInfo_Mesh CManager_Res::GetInfo_Mesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 메쉬가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_Mesh.find(a_rPath_Mesh) == m_oMapInfos_Mesh.end())
	{
		DWORD nNumMaterials = 0;
		STInfo_Mesh stInfo_Mesh = { 0 };

		LPD3DXMESH pXMesh = nullptr;
		LPD3DXBUFFER pXBuffer_Materials = nullptr;

		D3DXLoadMeshFromXA(a_rPath_Mesh.c_str(),
			D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), nullptr, &pXBuffer_Materials, nullptr, &nNumMaterials, &pXMesh);

		for(int i = 0; i < nNumMaterials; ++i)
		{
			D3DXMATERIAL stXMat;
			memcpy(&stXMat, (LPBYTE)pXBuffer_Materials->GetBufferPointer() + (sizeof(stXMat) * i), sizeof(stXMat));

			stInfo_Mesh.m_oVectorMaterials.push_back(stXMat.MatD3D);
			stInfo_Mesh.m_oVectorViews_SR.push_back(this->GetView_SR(stXMat.pTextureFilename));
		}
	}

	return m_oMapInfos_Mesh[a_rPath_Mesh];
}

STInfo_WaveSnd CManager_Res::GetInfo_WaveSnd(const std::string& a_rPath_Snd, bool a_bIsCreate_Auto)
{
	// 웨이브 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_WaveSnd.find(a_rPath_Snd) == m_oMapInfos_WaveSnd.end())
	{
		auto hMMIO = mmioOpenA((LPSTR)a_rPath_Snd.c_str(), nullptr, MMIO_READ);

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

		mmioRead(hMMIO, (LPSTR)&stInfo_WaveSnd.m_stInfo_Wave, sizeof(stInfo_WaveSnd.m_stInfo_Wave));
		mmioAscend(hMMIO, &stInfo_FmtChunk, 0);

		MMCKINFO stInfo_DataChunk;
		ZeroMemory(&stInfo_DataChunk, sizeof(stInfo_DataChunk));

		stInfo_DataChunk.fccType = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hMMIO, &stInfo_DataChunk, &stInfo_RIFF, MMIO_FINDCHUNK);

		stInfo_WaveSnd.m_pnBytes = (LPBYTE)malloc(stInfo_WaveSnd.m_nNumBytes);
		stInfo_WaveSnd.m_nNumBytes = stInfo_DataChunk.cksize;

		mmioRead(hMMIO, (LPSTR)stInfo_WaveSnd.m_pnBytes, stInfo_WaveSnd.m_nNumBytes);
		mmioClose(hMMIO, 0);

		m_oMapInfos_WaveSnd.insert(decltype(m_oMapInfos_WaveSnd)::value_type(a_rPath_Snd, stInfo_WaveSnd));
	}

	return m_oMapInfos_WaveSnd[a_rPath_Snd];
}

ID3D10Effect* CManager_Res::GetEffect(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto)
{
	// 이펙트가 없을 경우
	if(a_bIsCreate_Auto && m_oMapEffects.find(a_rPath_Effect) == m_oMapEffects.end())
	{
		ID3D10Blob* pError = nullptr;
		ID3D10Effect* pEffect = nullptr;

		D3DX10CreateEffectFromFileA(a_rPath_Effect.c_str(),
			nullptr, nullptr, VER_EFFECT.c_str(), D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, GET_APP_D3D()->GetDevice(), nullptr, nullptr, &pEffect, &pError, nullptr);

		// 에러가 존재 할 경우
		if(pError != nullptr)
		{
			printf("CManager_Res.GetEffect: %s\n", (char*)pError->GetBufferPointer());
		}

		m_oMapEffects.insert(decltype(m_oMapEffects)::value_type(a_rPath_Effect, pEffect));
	}

	return m_oMapEffects[a_rPath_Effect];
}

ID3D10ShaderResourceView* CManager_Res::GetView_SR(const std::string& a_rPath_Texture, bool a_bIsCreate_Auto)
{
	// 쉐이더 리소스 뷰가 없을 경우
	if(a_bIsCreate_Auto && m_oMapViews_SR.find(a_rPath_Texture) == m_oMapViews_SR.end())
	{
		ID3D10ShaderResourceView* pView_SR = nullptr;

		D3DX10CreateShaderResourceViewFromFileA(GET_APP_D3D()->GetDevice(),
			a_rPath_Texture.c_str(), nullptr, nullptr, &pView_SR, nullptr);

		m_oMapViews_SR.insert(decltype(m_oMapViews_SR)::value_type(a_rPath_Texture, pView_SR));
	}

	return m_oMapViews_SR[a_rPath_Texture];
}
