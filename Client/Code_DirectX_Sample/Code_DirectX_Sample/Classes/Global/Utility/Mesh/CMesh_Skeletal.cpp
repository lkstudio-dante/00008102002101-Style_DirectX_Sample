#include "CMesh_Skeletal.h"
#include "../Manager/CManager_Res.h"

CMesh_Skeletal::CMesh_Skeletal(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect)
{
	m_stInfo_SkeletalMesh = GET_MANAGER_RES()->GetInfo_SkeletalMesh(a_rPath_Mesh);
}

void CMesh_Skeletal::OnUpdate(float a_fTime_Delta)
{
	CObj_Render::OnUpdate(a_fTime_Delta);
	m_stInfo_SkeletalMesh.m_pXController_Anim->AdvanceTime(a_fTime_Delta, nullptr);
}

void CMesh_Skeletal::OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}
