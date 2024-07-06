#include "CManager_Res.h"
#include "../../Function/Func+Global.h"
#include "../Base/CApp_D3D.h"
#include "../Material/CMat.h"
#include "../Loader/CLoader_SkinningMesh.h"

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
	::DelResources(m_oMapLoaders_SkinningMesh);

	::ReleaseResources(m_oMapTextures);
	::ReleaseResources(m_oMapXEffects);

	for(auto& rstValType : m_oMapInfos_Mesh)
	{
		SAFE_FREE(rstValType.second.m_pnAdjacency);
		SAFE_RELEASE(rstValType.second.m_pXMesh);

		::ReleaseResources(rstValType.second.m_oVectorTextures);
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

		LPD3DXMESH pXMesh = nullptr;
		LPD3DXBUFFER pXBuffer_Adjacency = nullptr;
		LPD3DXBUFFER pXBuffer_Materials = nullptr;

		std::filesystem::path oPath(a_rPath_Mesh);
		auto oPath_Dir = oPath.parent_path();

		D3DXLoadMeshFromXA(a_rPath_Mesh.c_str(),
			D3DXMESH_MANAGED | D3DXMESH_32BIT, GET_APP_D3D()->GetDevice(), &pXBuffer_Adjacency, &pXBuffer_Materials, nullptr, &nNumMaterials, &pXMesh);

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

		pXMesh->CloneMesh(pXMesh->GetOptions(), 
			astElements_Vertex, GET_APP_D3D()->GetDevice(), &stInfo_Mesh.m_pXMesh);

		stInfo_Mesh.m_pnAdjacency = (LPDWORD)malloc(pXBuffer_Adjacency->GetBufferSize());

		for(int i = 0; i < nNumMaterials; ++i)
		{
			D3DXMATERIAL stXMat;
			memcpy(&stXMat, (LPD3DXMATERIAL)pXBuffer_Materials->GetBufferPointer() + i, sizeof(stXMat));

			std::string oPath_Texture = oPath_Dir.string() + "/" + stXMat.pTextureFilename;

			stInfo_Mesh.m_oVectorTextures.push_back(this->GetTexture(oPath_Texture));
			stInfo_Mesh.m_oVectorMaterials.push_back(stXMat.MatD3D);
		}

		stInfo_Mesh.m_pXMesh->Optimize(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(LPDWORD)pXBuffer_Adjacency->GetBufferPointer(), stInfo_Mesh.m_pnAdjacency, nullptr, nullptr, &stInfo_Mesh.m_pXMesh);

		m_oMapInfos_Mesh.insert(decltype(m_oMapInfos_Mesh)::value_type(a_rPath_Mesh, stInfo_Mesh));

		SAFE_RELEASE(pXMesh);
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

STInfo_SkinningMesh CManager_Res::GetInfo_SkinningMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 스키닝 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_SkinningMesh.find(a_rPath_Mesh) == m_oMapInfos_SkinningMesh.end())
	{
		auto pLoader_SkinningMesh = this->GetLoader_SkinningMesh(a_rPath_Mesh, a_bIsCreate_Auto);
		m_oMapInfos_SkinningMesh.insert(decltype(m_oMapInfos_SkinningMesh)::value_type(a_rPath_Mesh, pLoader_SkinningMesh->GetInfo_SkinningMesh()));
	}

	return m_oMapInfos_SkinningMesh[a_rPath_Mesh];
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

CLoader_SkinningMesh* CManager_Res::GetLoader_SkinningMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto)
{
	// 스키닝 메쉬 로더가 없을 경우
	if(a_bIsCreate_Auto && m_oMapLoaders_SkinningMesh.find(a_rPath_Mesh) == m_oMapLoaders_SkinningMesh.end())
	{
		auto pLoader_SkinningMesh = new CLoader_SkinningMesh(a_rPath_Mesh);
		m_oMapLoaders_SkinningMesh.insert(decltype(m_oMapLoaders_SkinningMesh)::value_type(a_rPath_Mesh, pLoader_SkinningMesh));
	}

	return m_oMapLoaders_SkinningMesh[a_rPath_Mesh];
}

LPDIRECT3DTEXTURE9 CManager_Res::GetTexture(const std::string& a_rPath_Texture, bool a_bIsCreate_Auto)
{
	// 텍스처가 없을 경우
	if(a_bIsCreate_Auto && m_oMapTextures.find(a_rPath_Texture) == m_oMapTextures.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = nullptr;
		D3DXCreateTextureFromFileA(GET_APP_D3D()->GetDevice(), a_rPath_Texture.c_str(), &pTexture);

		m_oMapTextures.insert(decltype(m_oMapTextures)::value_type(a_rPath_Texture, pTexture));
	}

	return m_oMapTextures[a_rPath_Texture];
}

LPD3DXEFFECT CManager_Res::GetXEffect(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto)
{
	// 이펙트가 없을 경우
	if(a_bIsCreate_Auto && m_oMapXEffects.find(a_rPath_Effect) == m_oMapXEffects.end())
	{
		LPD3DXBUFFER pError = nullptr;
		LPD3DXEFFECT pXEffect = nullptr;

		D3DXCreateEffectFromFileA(GET_APP_D3D()->GetDevice(),
			a_rPath_Effect.c_str(), nullptr, nullptr, D3DXSHADER_PACKMATRIX_ROWMAJOR, nullptr, &pXEffect, &pError);

		// 에러가 존재 할 경우
		if(pError != nullptr)
		{
			printf("CManager_Res.GetXEffect: %s\n", pError->GetBufferPointer());
		}

		SAFE_RELEASE(pError);
		m_oMapXEffects.insert(decltype(m_oMapXEffects)::value_type(a_rPath_Effect, pXEffect));
	}

	return m_oMapXEffects[a_rPath_Effect];
}
