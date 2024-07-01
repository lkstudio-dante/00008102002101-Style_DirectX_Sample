#include "CManager_Res.h"
#include "../../Function/Func+Global.h"
#include "../Base/CApp_D3D.h"
#include "../Material/CMat.h"
#include "../Loader/CLoader_SkeletonMesh.h"

/** 리소스를 제거한다 */
template <typename K, typename V>
static void DelResources(std::unordered_map<K, V>& a_rMapResources)
{
	for(auto& rstValType : a_rMapResources)
	{
		SAFE_DEL(rstValType.second);
	}
}

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
	::DelResources(m_oMapMaterials);
	::DelResources(m_oMapLoaders_SkeletonMesh);

	::ReleaseResources(m_oMapEffects);
	::ReleaseResources(m_oMapViews_SR);

	for(auto& rstValType : m_oMapInfos_Mesh)
	{
		SAFE_RELEASE(rstValType.second.m_pXMesh);
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
	// 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_Mesh.find(a_rPath_Mesh) == m_oMapInfos_Mesh.end())
	{
		DWORD nNumMaterials = 0;
		STInfo_Mesh stInfo_Mesh = { 0 };

		LPD3DXMESH pXMesh9 = nullptr;
		LPD3DXBUFFER pXBuffer_Adjacency = nullptr;
		LPD3DXBUFFER pXBuffer_Materials = nullptr;

		std::filesystem::path oPath(a_rPath_Mesh);
		auto oPath_Dir = oPath.parent_path();

		D3DXLoadMeshFromXA(a_rPath_Mesh.c_str(),
			D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), &pXBuffer_Adjacency, &pXBuffer_Materials, nullptr, &nNumMaterials, &pXMesh9);

		for(int i = 0; i < nNumMaterials; ++i)
		{
			D3DXMATERIAL stXMat;
			memcpy(&stXMat, (LPBYTE)pXBuffer_Materials->GetBufferPointer() + (sizeof(stXMat) * i), sizeof(stXMat));

			std::string oPath_Texture = oPath_Dir.string() + "/" + stXMat.pTextureFilename;

			stInfo_Mesh.m_oVectorMaterials.push_back(stXMat.MatD3D);
			stInfo_Mesh.m_oVectorViews_SR.push_back(this->GetView_SR(oPath_Texture));
		}

		pXMesh9->Optimize(D3DXMESHOPT_ATTRSORT, 
			(LPDWORD)pXBuffer_Adjacency->GetBufferPointer(), nullptr, nullptr, nullptr, &pXMesh9);

		stInfo_Mesh.m_pXMesh = Func::XMesh9ToXMesh(pXMesh9);
		m_oMapInfos_Mesh.insert(decltype(m_oMapInfos_Mesh)::value_type(a_rPath_Mesh, stInfo_Mesh));

		SAFE_RELEASE(pXMesh9);
		SAFE_RELEASE(pXBuffer_Adjacency);
		SAFE_RELEASE(pXBuffer_Materials);
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

STInfo_SkeletonMesh CManager_Res::GetInfo_SkeletonMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_SkeletonMesh.find(a_rPath_Mesh) == m_oMapInfos_SkeletonMesh.end())
	{
		auto pLoader_SkeletonMesh = this->GetLoader_SkeletonMesh(a_rPath_Mesh, a_bIsCreate_Auto);
		m_oMapInfos_SkeletonMesh.insert(decltype(m_oMapInfos_SkeletonMesh)::value_type(a_rPath_Mesh, pLoader_SkeletonMesh->GetInfo_SkeletonMesh()));
	}

	return m_oMapInfos_SkeletonMesh[a_rPath_Mesh];
}

CMat* CManager_Res::GetMat(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto)
{
	// 재질이 없을 경우
	if(a_bIsCreate_Auto && m_oMapMaterials.find(a_rPath_Effect) == m_oMapMaterials.end())
	{
		auto pMat = new CMat(a_rPath_Effect);
		m_oMapMaterials.insert(decltype(m_oMapMaterials)::value_type(a_rPath_Effect, pMat));
	}

	return m_oMapMaterials[a_rPath_Effect];
}

CLoader_SkeletonMesh* CManager_Res::GetLoader_SkeletonMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 로더가 없을 경우
	if(a_bIsCreate_Auto && m_oMapLoaders_SkeletonMesh.find(a_rPath_Mesh) == m_oMapLoaders_SkeletonMesh.end())
	{
		auto pLoader_SkeletonMesh = new CLoader_SkeletonMesh(a_rPath_Mesh);
		m_oMapLoaders_SkeletonMesh.insert(decltype(m_oMapLoaders_SkeletonMesh)::value_type(a_rPath_Mesh, pLoader_SkeletonMesh));
	}

	return m_oMapLoaders_SkeletonMesh[a_rPath_Mesh];
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
			SAFE_RELEASE(pError);
		}

		m_oMapEffects.insert(decltype(m_oMapEffects)::value_type(a_rPath_Effect, pEffect));
	}

	return m_oMapEffects[a_rPath_Effect];
}

ID3D10InputLayout* CManager_Res::GetInputLayout(ID3DX10Mesh* a_pXMesh, 
	const std::string& a_rPath_Effect, bool a_bIsCreate_Auto)
{
	// 입력 레이아웃이 없을 경우
	if(a_bIsCreate_Auto && m_oMapInputLayouts.find(a_rPath_Effect) == m_oMapInputLayouts.end())
	{
		D3D10_PASS_DESC stDesc_Pass;
		this->GetEffect(a_rPath_Effect)->GetTechniqueByIndex(0)->GetPassByIndex(0)->GetDesc(&stDesc_Pass);
	}

	return m_oMapInputLayouts[a_rPath_Effect];
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
