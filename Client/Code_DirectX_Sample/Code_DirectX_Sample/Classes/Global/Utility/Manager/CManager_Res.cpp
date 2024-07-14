#include "CManager_Res.h"
#include "../../Function/Func+Global.h"
#include "../Base/CApp_D3D.h"
#include "../Material/CMat.h"
#include "../Loader/CLoader_SkeletalMesh.h"

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
	::DelResources(m_oMapLoaders_SkeletalMesh);

	::ReleaseResources(m_oMapViews_SR);
	::ReleaseResources(m_oMapEffects);

	for(auto& rstValType : m_oMapInfos_Mesh)
	{
		SAFE_FREE(rstValType.second.m_pnAdjacency);
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
		LPD3DXMESH pXMesh_Clone9 = nullptr;

		LPD3DXBUFFER pXBuffer_Adjacency9 = nullptr;
		LPD3DXBUFFER pXBuffer_Materials9 = nullptr;

		std::filesystem::path oPath(a_rPath_Mesh);
		auto oPath_Dir = oPath.parent_path();

		D3DXLoadMeshFromXA(a_rPath_Mesh.c_str(),
			D3DXMESH_MANAGED | D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), &pXBuffer_Adjacency9, &pXBuffer_Materials9, nullptr, &nNumMaterials, &pXMesh9);

		D3DVERTEXELEMENT9 astElements_Vertex[MAX_FVF_DECL_SIZE] =
		{
			{ 0, offsetof(STVertex, m_stPos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, offsetof(STVertex, m_stColor), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
			{ 0, offsetof(STVertex, m_stNormal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, offsetof(STVertex, m_stTangent), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
			{ 0, offsetof(STVertex, m_stBinormal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
			{ 0, offsetof(STVertex, m_stUV), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};

		pXMesh9->CloneMesh(pXMesh9->GetOptions(), 
			astElements_Vertex, GET_APP_D3D()->GetDevice9(), &pXMesh_Clone9);

		stInfo_Mesh.m_pnAdjacency = (LPDWORD)malloc(pXBuffer_Adjacency9->GetBufferSize());

		for(int i = 0; i < nNumMaterials; ++i)
		{
			D3DXMATERIAL stXMat;
			memcpy(&stXMat, (LPD3DXMATERIAL)pXBuffer_Materials9->GetBufferPointer() + i, sizeof(stXMat));

			std::string oPath_Texture = oPath_Dir.string() + "/" + stXMat.pTextureFilename;

			stInfo_Mesh.m_oVectorViews_SR.push_back(this->GetView_SR(oPath_Texture));
			stInfo_Mesh.m_oVectorMaterials.push_back(stXMat.MatD3D);
		}

		pXMesh_Clone9->Optimize(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(LPDWORD)pXBuffer_Adjacency9->GetBufferPointer(), stInfo_Mesh.m_pnAdjacency, nullptr, nullptr, &pXMesh_Clone9);

		stInfo_Mesh.m_pXMesh = Func::XMesh9ToXMesh(pXMesh_Clone9);
		m_oMapInfos_Mesh.insert(decltype(m_oMapInfos_Mesh)::value_type(a_rPath_Mesh, stInfo_Mesh));

		SAFE_RELEASE(pXMesh9);
		SAFE_RELEASE(pXMesh_Clone9);

		SAFE_RELEASE(pXBuffer_Adjacency9);
		SAFE_RELEASE(pXBuffer_Materials9);
	}

	return m_oMapInfos_Mesh[a_rPath_Mesh];
}

STInfo_WaveSnd CManager_Res::GetInfo_WaveSnd(const std::string& a_rPath_Snd, bool a_bIsCreate_Auto)
{
	// 웨이브 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_WaveSnd.find(a_rPath_Snd) == m_oMapInfos_WaveSnd.end())
	{
		auto hMMIO = mmioOpenA((LPSTR)a_rPath_Snd.c_str(), nullptr, MMIO_READ);
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

STInfo_SkeletalMesh CManager_Res::GetInfo_SkeletalMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_SkeletalMesh.find(a_rPath_Mesh) == m_oMapInfos_SkeletalMesh.end())
	{
		auto pLoader_SkeletalMesh = this->GetLoader_SkeletalMesh(a_rPath_Mesh, a_bIsCreate_Auto);
		m_oMapInfos_SkeletalMesh.insert(decltype(m_oMapInfos_SkeletalMesh)::value_type(a_rPath_Mesh, pLoader_SkeletalMesh->GetInfo_SkeletalMesh()));
	}

	return m_oMapInfos_SkeletalMesh[a_rPath_Mesh];
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

CLoader_SkeletalMesh* CManager_Res::GetLoader_SkeletalMesh(const std::string& a_rPath_Mesh, 
	bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 로더가 없을 경우
	if(a_bIsCreate_Auto && m_oMapLoaders_SkeletalMesh.find(a_rPath_Mesh) == m_oMapLoaders_SkeletalMesh.end())
	{
		auto pLoader_SkeletalMesh = new CLoader_SkeletalMesh(a_rPath_Mesh);
		m_oMapLoaders_SkeletalMesh.insert(decltype(m_oMapLoaders_SkeletalMesh)::value_type(a_rPath_Mesh, pLoader_SkeletalMesh));
	}

	return m_oMapLoaders_SkeletalMesh[a_rPath_Mesh];
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
			printf("CManager_Res.GetXEffect: %s\n", pError->GetBufferPointer());
		}

		SAFE_RELEASE(pError);
		m_oMapEffects.insert(decltype(m_oMapEffects)::value_type(a_rPath_Effect, pEffect));
	}

	return m_oMapEffects[a_rPath_Effect];
}

ID3D10InputLayout* CManager_Res::GetInputLayout(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 입력 레이아웃이 없을 경우
	if(a_bIsCreate_Auto && m_oMapInputLayouts.find(a_rPath_Mesh) == m_oMapInputLayouts.end())
	{
		auto stInfo_Mesh = this->GetInfo_Mesh(a_rPath_Mesh, a_bIsCreate_Auto);
	}

	return m_oMapInputLayouts[a_rPath_Mesh];
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
