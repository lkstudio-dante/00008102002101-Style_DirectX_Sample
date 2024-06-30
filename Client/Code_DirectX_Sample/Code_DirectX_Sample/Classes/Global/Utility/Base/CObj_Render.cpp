#include "CObj_Render.h"
#include "CApp_D3D.h"
#include "../Camera/CCamera.h"
#include "../Material/CMat.h"
#include "../Manager/CManager_Res.h"

CObj_Render::CObj_Render(const std::string& a_rPath_Effect)
{
	m_pMat = new CMat(a_rPath_Effect);
}

void CObj_Render::OnRender(ID3D10Device* a_pDevice)
{
	CObj::OnRender(a_pDevice);
	m_pMat->SetMatrix(NAME_WORLD_MATRIX_CBUFFER, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](ID3D10EffectPass* a_pPass) -> void
	{
		a_pPass->Apply(0);
		this->OnRender(a_pDevice, a_pPass);
	});
}

void CObj_Render::OnLateRender(ID3D10Device* a_pDevice)
{
	CObj::OnLateRender(a_pDevice);
	m_pMat->SetMatrix(NAME_WORLD_MATRIX_CBUFFER, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](ID3D10EffectPass* a_pPass) -> void
	{
		a_pPass->Apply(0);
		this->OnLateRender(a_pDevice, a_pPass);
	});
}

void CObj_Render::OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}

void CObj_Render::OnLateRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}
