#include "CLoader_SkeletalMesh.h"
#include "../../Function/CFunc+DirectX_Abs.h"

#include "../Manager/CManager_D3DRes.h"
#include "../Base/CApp_D3D.h"

CLoader_SkeletalMesh::CLoader_SkeletalMesh(const std::string& a_rPath_Mesh)
	:
	m_oPath_Mesh(a_rPath_Mesh)
{
	ZeroMemory(&m_stInfo_SkeletalMesh, sizeof(m_stInfo_SkeletalMesh));

	D3DXLoadMeshHierarchyFromXA(a_rPath_Mesh.c_str(),
		D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), this, nullptr, &m_stInfo_SkeletalMesh.m_pstXFrame, &m_stInfo_SkeletalMesh.m_pXController_Anim);
}

HRESULT CLoader_SkeletalMesh::CreateFrame(LPCSTR a_pszName, LPD3DXFRAME* a_pstOutXFrame)
{
	auto pstInfo_Bone = new STInfo_Bone();

	pstInfo_Bone->Name = (LPSTR)malloc(sizeof(CHAR) * (strlen(a_pszName) + 1));
	strcpy(pstInfo_Bone->Name, a_pszName);

	D3DXMatrixIdentity(&pstInfo_Bone->TransformationMatrix);
	D3DXMatrixIdentity(&pstInfo_Bone->m_stMatrix_CombineTrans);

	*a_pstOutXFrame = pstInfo_Bone;
	return S_OK;
}

HRESULT CLoader_SkeletalMesh::CreateMeshContainer(LPCSTR a_pszName,
	const D3DXMESHDATA* a_pstXData_Mesh, const D3DXMATERIAL* a_pstXMaterials, const D3DXEFFECTINSTANCE* a_pstXInst_Effect, DWORD a_nNumMaterials, const DWORD* a_pnAdjacency, LPD3DXSKININFO a_pstXInfo_Skin, LPD3DXMESHCONTAINER* a_pstOutXContainer_Mesh)
{
	auto pstInfo_MeshContainer = new STInfo_MeshContainer();
	pstInfo_MeshContainer->Name = (LPSTR)malloc(sizeof(CHAR) * (strlen(a_pszName) + 1));

	strcpy(pstInfo_MeshContainer->Name, a_pszName);
	pstInfo_MeshContainer->pAdjacency = (LPDWORD)malloc(sizeof(DWORD) * a_pstXData_Mesh->pMesh->GetNumFaces());

	CopyMemory(pstInfo_MeshContainer->pAdjacency, 
		a_pnAdjacency, sizeof(DWORD) * a_pstXData_Mesh->pMesh->GetNumFaces());

	this->SetupMat(pstInfo_MeshContainer, a_pstXMaterials, a_nNumMaterials);
	this->SetupMesh(pstInfo_MeshContainer, a_pstXData_Mesh, a_pstXInfo_Skin);

	*a_pstOutXContainer_Mesh = pstInfo_MeshContainer;
	return S_OK;
}

HRESULT CLoader_SkeletalMesh::DestroyFrame(LPD3DXFRAME a_pstXFrame)
{
	SAFE_FREE(a_pstXFrame->Name);
	SAFE_DELETE(a_pstXFrame);

	return S_OK;
}

HRESULT CLoader_SkeletalMesh::DestroyMeshContainer(LPD3DXMESHCONTAINER a_pstXContainer_Mesh)
{
	SAFE_FREE(a_pstXContainer_Mesh->Name);
	SAFE_FREE(a_pstXContainer_Mesh->pAdjacency);

	SAFE_DELETE(a_pstXContainer_Mesh);
	return S_OK;
}

void CLoader_SkeletalMesh::SetupMat(STInfo_MeshContainer* a_pstInfo_MeshContainer,
	const D3DXMATERIAL* a_pstXMaterials, const int a_nNumMaterials)
{
	a_pstInfo_MeshContainer->NumMaterials = a_nNumMaterials;
	a_pstInfo_MeshContainer->pMaterials = (D3DXMATERIAL*)malloc(sizeof(D3DXMATERIAL) * a_pstInfo_MeshContainer->NumMaterials);

	CopyMemory(a_pstInfo_MeshContainer->pMaterials,
		a_pstXMaterials, sizeof(D3DXMATERIAL) * a_pstInfo_MeshContainer->NumMaterials);

	std::filesystem::path oPath(m_oPath_Mesh);
	auto oPath_Dir = oPath.parent_path();

	for(int i = 0; i < a_pstInfo_MeshContainer->NumMaterials; ++i)
	{
		std::string oPath_Texture = oPath_Dir.string() + 
			"/" + a_pstXMaterials[i].pTextureFilename;

		a_pstInfo_MeshContainer->m_oVectorViews_SR.push_back(GET_MANAGER_D3D_RES()->GetView_SR(oPath_Texture));
		a_pstInfo_MeshContainer->m_oVectorMaterials.push_back(a_pstXMaterials[i].MatD3D);
	}
}

void CLoader_SkeletalMesh::SetupMesh(STInfo_MeshContainer* a_pstInfo_MeshContainer,
	const D3DXMESHDATA* a_pstXData_Mesh, LPD3DXSKININFO a_pstXInfo_Skin)
{
	a_pstInfo_MeshContainer->MeshData = *a_pstXData_Mesh;
	a_pstInfo_MeshContainer->MeshData.pMesh->AddRef();

	a_pstInfo_MeshContainer->pSkinInfo = a_pstXInfo_Skin;
	a_pstInfo_MeshContainer->pSkinInfo->AddRef();

	for(int i = 0; i < a_pstInfo_MeshContainer->pSkinInfo->GetNumBones(); ++i)
	{
		auto stMatrix_BoneOffset = *a_pstInfo_MeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);
		a_pstInfo_MeshContainer->m_oVectorXMatrices_BoneOffset.push_back(stMatrix_BoneOffset);
	}

	DWORD nNumIDs_Bone = 0;
	DWORD nNumCombinations_Bone = 0;

	LPD3DXMESH pXMesh = nullptr;
	LPD3DXBUFFER pXBuffer_BoneCombination = nullptr;

	a_pstInfo_MeshContainer->pSkinInfo->ConvertToBlendedMesh(a_pstInfo_MeshContainer->MeshData.pMesh,
		D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE, a_pstInfo_MeshContainer->pAdjacency, a_pstInfo_MeshContainer->pAdjacency, nullptr, nullptr, &nNumIDs_Bone, &nNumCombinations_Bone, &pXBuffer_BoneCombination, &pXMesh);

	auto pstXCombinations_Bone = (LPD3DXBONECOMBINATION)pXBuffer_BoneCombination->GetBufferPointer();

	for(int i = 0; i < nNumCombinations_Bone; ++i)
	{
		D3DXBONECOMBINATION stXCombination_Bone;
		CopyMemory(&stXCombination_Bone, pstXCombinations_Bone + i, sizeof(stXCombination_Bone));

		stXCombination_Bone.BoneId = (LPDWORD)malloc(sizeof(DWORD) * nNumIDs_Bone);

		CopyMemory(stXCombination_Bone.BoneId, 
			pstXCombinations_Bone[i].BoneId, sizeof(DWORD) * nNumIDs_Bone);

		a_pstInfo_MeshContainer->m_oVectorXCombinations_Bone.push_back(stXCombination_Bone);
	}

	a_pstInfo_MeshContainer->m_pXMesh = CFunc::XMesh9ToXMesh(pXMesh);

	SAFE_RELEASE(pXMesh);
	SAFE_RELEASE(pXBuffer_BoneCombination);
}
