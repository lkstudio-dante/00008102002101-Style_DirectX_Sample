#include "CMesh_Skeleton.h"
#include "../Manager/CManager_Res.h"

CMesh_Skeleton::CMesh_Skeleton(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect)
{
	m_stInfo_SkeletonMesh = GET_MANAGER_RES()->GetInfo_SkeletonMesh(a_rPath_Mesh);
}

void CMesh_Skeleton::OnUpdate(float a_fTime_Delta)
{
	CObj_Render::OnUpdate(a_fTime_Delta);
	m_stInfo_SkeletonMesh.m_pXController_Anim->AdvanceTime(a_fTime_Delta, nullptr);
}

void CMesh_Skeleton::OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}
