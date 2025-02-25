#include "CGrid.h"
#include "../Mesh/CMesh.h"
#include "../Base/CApp_D3D.h"

CGrid::CGrid(const std::string& a_rPath_Effect, const SIZE& a_rstSize)
	:
	CObj_Debug(a_rPath_Effect),
	m_stSize(a_rstSize)
{
	// Do Something
}

void CGrid::Render(ID3D10Device* a_pDevice)
{
	CObj_Debug::Render(a_pDevice);
}

CMesh* CGrid::CreateMesh(const std::string& a_rPath_Effect)
{
	STInfo_Mesh stInfo_Mesh;
	stInfo_Mesh.m_oVectorDescs_InputElement = G_LIST_DESCS_DEBUG_INPUT_ELEMENT();

	return nullptr;
}
