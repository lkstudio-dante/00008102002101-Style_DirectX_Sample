#include "CObj_Render.h"
#include "CApp_D3D.h"
#include "../Camera/CCamera.h"
#include "../Material/CMat.h"
#include "../Manager/CManager_Res.h"

CObj_Render::CObj_Render(const std::string& a_rPath_Effect)
{
	m_pMat = new CMat(a_rPath_Effect);
}

void CObj_Render::OnRender(LPDIRECT3DDEVICE9 a_pDevice)
{
	CObj::OnRender(a_pDevice);
	m_pMat->SetMatrix(NAME_WORLD_MATRIX_CBUFFER, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](int a_nIdx) -> void
	{
		this->OnRender(a_pDevice, a_nIdx);
	});
}

void CObj_Render::OnLateRender(LPDIRECT3DDEVICE9 a_pDevice)
{
	CObj::OnLateRender(a_pDevice);
	m_pMat->SetMatrix(NAME_WORLD_MATRIX_CBUFFER, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](int a_nIdx) -> void
	{
		this->OnLateRender(a_pDevice, a_nIdx);
	});
}

void CObj_Render::OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass)
{
	// Do Something
}

void CObj_Render::OnLateRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass)
{
	// Do Something
}
