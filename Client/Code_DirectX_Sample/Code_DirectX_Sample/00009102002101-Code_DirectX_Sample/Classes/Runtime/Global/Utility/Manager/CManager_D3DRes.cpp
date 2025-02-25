#include "CManager_D3DRes.h"
#include "../../Function/CFunc+DirectX_Abs.h"

#include "../Material/CMat.h"
#include "../Loader/CLoader_SkeletalMesh.h"
#include "../Base/CApp_D3D.h"

CManager_D3DRes::CManager_D3DRes(void)
{
	// Do Something
}

CManager_D3DRes::~CManager_D3DRes(void)
{
	// Do Something
}

void CManager_D3DRes::Release(void)
{
	CFunc::DeleteResources(m_oMapMaterials);
	CFunc::DeleteResources(m_oMapLoaders_SkeletalMesh);

	CFunc::ReleaseResources(m_oMapViews_SR);
	CFunc::ReleaseResources(m_oMapEffects);

	for(auto& rstValType : m_oMapInfos_Mesh)
	{
		SAFE_FREE(rstValType.second.m_pnAdjacency);
		SAFE_RELEASE(rstValType.second.m_pXMesh);

		CFunc::ReleaseResources(rstValType.second.m_oVectorViews_SR);
	}
}

STInfo_Mesh CManager_D3DRes::GetInfo_Mesh(const std::string& a_rKey, 
	bool a_bIsCreate_Auto)
{
	// 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_Mesh.find(a_rKey) == m_oMapInfos_Mesh.end())
	{
		DWORD nNumMaterials = 0;
		STInfo_Mesh stInfo_Mesh = { 0 };

		LPD3DXMESH pXMesh9 = nullptr;
		LPD3DXMESH pXMesh_Clone9 = nullptr;

		LPD3DXBUFFER pXBuffer_Adjacency9 = nullptr;
		LPD3DXBUFFER pXBuffer_Materials9 = nullptr;

		std::filesystem::path oPath(a_rKey);
		auto oPath_Dir = oPath.parent_path();

		D3DXLoadMeshFromXA(a_rKey.c_str(),
			D3DXMESH_MANAGED | D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), &pXBuffer_Adjacency9, &pXBuffer_Materials9, nullptr, &nNumMaterials, &pXMesh9);

		pXMesh9->CloneMesh(pXMesh9->GetOptions(),
			G_LIST_VERTEX_ELEMENTS_DEF().begin(), GET_APP_D3D()->GetDevice9(), &pXMesh_Clone9);

		stInfo_Mesh.m_pnAdjacency = (LPDWORD)malloc(pXBuffer_Adjacency9->GetBufferSize());
		stInfo_Mesh.m_oVectorDescs_InputElement = CFunc::VertexDeclToInputLayout(G_LIST_VERTEX_ELEMENTS_DEF().begin());

		for(int i = 0; i < nNumMaterials; ++i)
		{
			D3DXMATERIAL stXMat;

			CopyMemory(&stXMat, 
				(LPD3DXMATERIAL)pXBuffer_Materials9->GetBufferPointer() + i, sizeof(stXMat));

			std::string oPath_Texture = oPath_Dir.string() + "/" + stXMat.pTextureFilename;

			stInfo_Mesh.m_oVectorViews_SR.push_back(this->GetView_SR(oPath_Texture));
			stInfo_Mesh.m_oVectorMaterials.push_back(stXMat.MatD3D);
		}

		pXMesh_Clone9->Optimize(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(LPDWORD)pXBuffer_Adjacency9->GetBufferPointer(), stInfo_Mesh.m_pnAdjacency, nullptr, nullptr, &pXMesh_Clone9);

		stInfo_Mesh.m_pXMesh = CFunc::XMesh9ToXMesh(pXMesh_Clone9);
		CFunc::InsertVal(m_oMapInfos_Mesh, a_rKey, stInfo_Mesh);

		SAFE_RELEASE(pXMesh9);
		SAFE_RELEASE(pXMesh_Clone9);

		SAFE_RELEASE(pXBuffer_Adjacency9);
		SAFE_RELEASE(pXBuffer_Materials9);
	}

	return m_oMapInfos_Mesh[a_rKey];
}

STInfo_SkeletalMesh CManager_D3DRes::GetInfo_SkeletalMesh(const std::string& a_rKey, 
	bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 정보가 없을 경우
	if(a_bIsCreate_Auto && m_oMapInfos_SkeletalMesh.find(a_rKey) == m_oMapInfos_SkeletalMesh.end())
	{
		auto pLoader_SkeletalMesh = this->GetLoader_SkeletalMesh(a_rKey, a_bIsCreate_Auto);

		CFunc::InsertVal(m_oMapInfos_SkeletalMesh, 
			a_rKey, pLoader_SkeletalMesh->GetInfo_SkeletalMesh());
	}

	return m_oMapInfos_SkeletalMesh[a_rKey];
}

CMat* CManager_D3DRes::GetMat(const std::string& a_rKey, bool a_bIsCreate_Auto)
{
	// 재질이 없을 경우
	if(a_bIsCreate_Auto && m_oMapMaterials.find(a_rKey) == m_oMapMaterials.end())
	{
		auto pMat = new CMat(a_rKey);
		CFunc::InsertVal(m_oMapMaterials, a_rKey, pMat);
	}

	return m_oMapMaterials[a_rKey];
}

CLoader_SkeletalMesh* CManager_D3DRes::GetLoader_SkeletalMesh(const std::string& a_rKey, 
	bool a_bIsCreate_Auto)
{
	// 스켈레톤 메쉬 로더가 없을 경우
	if(a_bIsCreate_Auto && m_oMapLoaders_SkeletalMesh.find(a_rKey) == m_oMapLoaders_SkeletalMesh.end())
	{
		auto pLoader_SkeletalMesh = new CLoader_SkeletalMesh(a_rKey);
		CFunc::InsertVal(m_oMapLoaders_SkeletalMesh, a_rKey, pLoader_SkeletalMesh);
	}

	return m_oMapLoaders_SkeletalMesh[a_rKey];
}

ID3D10Effect* CManager_D3DRes::GetEffect(const std::string& a_rKey, bool a_bIsCreate_Auto)
{
	// 이펙트가 없을 경우
	if(a_bIsCreate_Auto && m_oMapEffects.find(a_rKey) == m_oMapEffects.end())
	{
		ID3D10Blob* pError = nullptr;
		ID3D10Effect* pEffect = nullptr;

		D3DX10CreateEffectFromFileA(a_rKey.c_str(),
			nullptr, nullptr, ::G_VER_EFFECT.c_str(), D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, GET_APP_D3D()->GetDevice(), nullptr, nullptr, &pEffect, &pError, nullptr);

		// 에러가 존재 할 경우
		if(pError != nullptr)
		{
			printf("%s: %s\n", __FUNCTION__, pError->GetBufferPointer());
		}

		SAFE_RELEASE(pError);
		CFunc::InsertVal(m_oMapEffects, a_rKey, pEffect);
	}

	return m_oMapEffects[a_rKey];
}

ID3D10InputLayout* CManager_D3DRes::GetInputLayout(const std::string& a_rKey, 
	bool a_bIsCreate_Auto)
{
	// 입력 레이아웃이 없을 경우
	if(a_bIsCreate_Auto && m_oMapInputLayouts.find(a_rKey) == m_oMapInputLayouts.end())
	{
		//auto stInfo_Mesh = this->GetInfo_Mesh(a_rKey, a_bIsCreate_Auto);
		//ID3D10InputLayout* pInputLayout = nullptr;

		//GET_APP_D3D()->GetDevice()->CreateInputLayout(&stInfo_Mesh.m_oVectorDescs_InputElement[0],
		//	stInfo_Mesh.m_oVectorDescs_InputElement.size(),

		// TODO: 구현 필요
	}

	return m_oMapInputLayouts[a_rKey];
}

ID3D10ShaderResourceView* CManager_D3DRes::GetView_SR(const std::string& a_rKey, 
	bool a_bIsCreate_Auto)
{
	// 쉐이더 리소스 뷰가 없을 경우
	if(a_bIsCreate_Auto && m_oMapViews_SR.find(a_rKey) == m_oMapViews_SR.end())
	{
		ID3D10ShaderResourceView* pView_SR = nullptr;

		D3DX10CreateShaderResourceViewFromFileA(GET_APP_D3D()->GetDevice(),
			a_rKey.c_str(), nullptr, nullptr, &pView_SR, nullptr);

		CFunc::InsertVal(m_oMapViews_SR, a_rKey, pView_SR);
	}

	return m_oMapViews_SR[a_rKey];
}
