#include "CLoader_SkeletalMesh.h"
#include "../Base/CApp_D3D.h"

CLoader_SkeletalMesh::CLoader_SkeletalMesh(const std::string& a_rPath_Mesh)
{
	ZeroMemory(&m_stInfo_SkeletalMesh, sizeof(m_stInfo_SkeletalMesh));

	D3DXLoadMeshHierarchyFromXA(a_rPath_Mesh.c_str(),
		D3DXMESH_32BIT, GET_APP_D3D()->GetDevice9(), this, nullptr, &m_stInfo_SkeletalMesh.m_pstXFrame, &m_stInfo_SkeletalMesh.m_pXController_Anim);
}

HRESULT CLoader_SkeletalMesh::CreateFrame(LPCSTR a_pszName, LPD3DXFRAME* a_pstOutXFrame)
{
	auto pstInfo_Bone = (STInfo_Bone*)malloc(sizeof(STInfo_Bone));
	ZeroMemory(pstInfo_Bone, sizeof(STInfo_Bone));

	pstInfo_Bone->Name = (LPSTR)malloc(sizeof(CHAR) * (strlen(a_pszName) + 1));
	strcpy(pstInfo_Bone->Name, a_pszName);

	D3DXMatrixIdentity(&pstInfo_Bone->TransformationMatrix);
	D3DXMatrixIdentity(&pstInfo_Bone->m_stMatrix_CombineTrans);

	*a_pstOutXFrame = pstInfo_Bone;
	return S_OK;
}

HRESULT CLoader_SkeletalMesh::CreateMeshContainer(LPCSTR a_pszName, 
	const D3DXMESHDATA* a_pstXData_Mesh, const D3DXMATERIAL* a_pstXMat, const D3DXEFFECTINSTANCE* a_pstXInst_Effect, DWORD a_nNumMaterials, const DWORD* a_pAdjacency, LPD3DXSKININFO a_pstXInfo_Skin, LPD3DXMESHCONTAINER* a_pstOutXContainer_Mesh)
{
	auto pstInfo_MeshContainer = (STInfo_MeshContainer*)malloc(sizeof(STInfo_MeshContainer));
	ZeroMemory(pstInfo_MeshContainer, sizeof(STInfo_MeshContainer));

	pstInfo_MeshContainer->Name = (LPSTR)malloc(sizeof(CHAR) * (strlen(a_pszName) + 1));
	strcpy(pstInfo_MeshContainer->Name, a_pszName);

	*a_pstOutXContainer_Mesh = pstInfo_MeshContainer;
	return S_OK;
}

HRESULT CLoader_SkeletalMesh::DestroyFrame(LPD3DXFRAME a_pstXFrame)
{
	SAFE_FREE(a_pstXFrame->Name);
	SAFE_FREE(a_pstXFrame);

	return S_OK;
}

HRESULT CLoader_SkeletalMesh::DestroyMeshContainer(LPD3DXMESHCONTAINER a_pstXContainer_Mesh)
{
	SAFE_FREE(a_pstXContainer_Mesh->Name);
	SAFE_FREE(a_pstXContainer_Mesh);

	return S_OK;
}
