#include "CMesh.h"
#include "../Manager/CManager_Res.h"

CMesh::CMesh(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect)
	:
	CObj_Render(a_rPath_Effect)
{
	m_stInfo_Mesh = GET_MANAGER_RES()->GetInfo_Mesh(a_rPath_Mesh);
	m_pCBuffer_DiffuseMap = this->GetEffect()->GetConstantBufferByName(NAME_DIFFUSE_MAP_CBUFFER.c_str())->AsShaderResource();
}

void CMesh::OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	for(int i = 0; i < m_stInfo_Mesh.m_oVectorMaterials.size(); ++i)
	{
		m_pCBuffer_DiffuseMap->SetResource(m_stInfo_Mesh.m_oVectorViews_SR[i]);
		m_stInfo_Mesh.m_pMesh->DrawSubset(i);
	}
}
