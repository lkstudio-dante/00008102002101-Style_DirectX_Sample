#include "CMesh_Skinning.h"
#include "../Manager/CManager_Res.h"

CMesh_Skinning::CMesh_Skinning(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect)
{
	m_stInfo_SkinningMesh = GET_MANAGER_RES()->GetInfo_SkinningMesh(a_rPath_Mesh);
}

void CMesh_Skinning::OnUpdate(float a_fTime_Delta)
{
	CObj_Render::OnUpdate(a_fTime_Delta);
	m_stInfo_SkinningMesh.m_pXController_Anim->AdvanceTime(a_fTime_Delta, nullptr);
}

void CMesh_Skinning::OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass)
{
	// Do Something
}
