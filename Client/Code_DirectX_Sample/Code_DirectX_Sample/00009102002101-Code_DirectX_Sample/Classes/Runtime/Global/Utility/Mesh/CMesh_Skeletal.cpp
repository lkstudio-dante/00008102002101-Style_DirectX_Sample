#include "CMesh_Skeletal.h"
#include "../Manager/CManager_D3DRes.h"

CMesh_Skeletal::CMesh_Skeletal(const std::string& a_rPath_Mesh, 
	const std::string& a_rPath_Effect)
	:
	CMesh_Skeletal(GET_MANAGER_D3D_RES()->GetInfo_SkeletalMesh(a_rPath_Mesh), a_rPath_Effect)
{
	// Do Something
}

CMesh_Skeletal::CMesh_Skeletal(const STInfo_SkeletalMesh& a_rstInfo_SkeletalMesh,
	const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect),
	m_stInfo_SkeletalMesh(a_rstInfo_SkeletalMesh)
{
	// Do Something
}

void CMesh_Skeletal::Update(float a_fTime_Delta)
{
	CObj_Render::Update(a_fTime_Delta);
	m_stInfo_SkeletalMesh.m_pXController_Anim->AdvanceTime(a_fTime_Delta, nullptr);

	this->OnUpdateState_Bone(static_cast<STInfo_Bone*>(m_stInfo_SkeletalMesh.m_pstXFrame),
		this->GetMatrix_WorldTrans());
}

void CMesh_Skeletal::Render(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	auto pstMeshContainer = m_stInfo_SkeletalMesh.m_pstXFrame->pMeshContainer;

	while(pstMeshContainer != nullptr)
	{
		this->OnRender_MeshContainer(a_pDevice, a_pPass, pstMeshContainer);
		pstMeshContainer = pstMeshContainer->pNextMeshContainer;
	}
}

void CMesh_Skeletal::OnUpdateState_Bone(LPD3DXFRAME a_pstXFrame, 
	const D3DXMATRIXA16& a_rstMatrix_Parent)
{
	// 본 상태 갱신이 불가능 할 경우
	if(a_pstXFrame == nullptr)
	{
		return;
	}

	this->OnUpdateState_Bone(a_pstXFrame->pFrameSibling, a_rstMatrix_Parent);
	this->OnUpdateState_Bone(a_pstXFrame->pFrameFirstChild, a_rstMatrix_Parent);
}

void CMesh_Skeletal::OnRender_MeshContainer(ID3D10Device* a_pDevice,
	ID3D10EffectPass* a_pPass, LPD3DXMESHCONTAINER a_pstMeshContainer)
{
	// 컨테이너 그리기가 불가능 할 경우
	if(a_pstMeshContainer == nullptr)
	{
		return;
	}
}
