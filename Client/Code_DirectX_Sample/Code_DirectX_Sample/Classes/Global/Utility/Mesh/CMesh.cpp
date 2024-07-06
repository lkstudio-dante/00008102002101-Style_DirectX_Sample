#include "CMesh.h"
#include "../Manager/CManager_Res.h"

CMesh::CMesh(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect)
{
	m_stInfo_Mesh = GET_MANAGER_RES()->GetInfo_Mesh(a_rPath_Mesh);
}

void CMesh::OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass)
{
	CObj_Render::OnRender(a_pDevice, a_nIdx_Pass);

	for(int i = 0; i < m_stInfo_Mesh.m_oVectorMaterials.size(); ++i)
	{
		m_stInfo_Mesh.m_pXMesh->DrawSubset(i);
	}
}
