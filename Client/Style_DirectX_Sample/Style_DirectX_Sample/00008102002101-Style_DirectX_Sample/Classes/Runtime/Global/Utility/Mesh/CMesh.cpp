#include "CMesh.h"
#include "../Manager/CManager_D3DRes.h"

CMesh::CMesh(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CMesh(GET_MANAGER_D3D_RES()->GetInfo_Mesh(a_rPath_Mesh), a_rPath_Effect)
{
	// Do Something
}

CMesh::CMesh(const STInfo_Mesh& a_rstInfo_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect),
	m_stInfo_Mesh(a_rstInfo_Mesh)
{
	// Do Something
}

void CMesh::Render(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	CObj_Render::Render(a_pDevice, a_pPass);

	for(int i = 0; i < m_stInfo_Mesh.m_oVectorMaterials.size(); ++i)
	{
		m_stInfo_Mesh.m_pXMesh->DrawSubset(i);
	}
}
