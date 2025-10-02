#include "CObj_Render.h"

#include "../Camera/CCamera.h"
#include "../Material/CMat.h"
#include "../Manager/CManager_D3DRes.h"

CObj_Render::CObj_Render(const std::string& a_rPath_Effect)
	:
	m_oPath_Effect(a_rPath_Effect)
{
	// Do Something
}

void CObj_Render::Init(void)
{
	CObj_D3D::Init();
	m_pMat = GET_MANAGER_D3D_RES()->GetMat(m_oPath_Effect);
}

void CObj_Render::Render(ID3D10Device* a_pDevice)
{
	m_pMat->SetMatrix(::G_N_CBUFFER_WORLD_MATRIX, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](auto a_pPass) -> void
	{
		this->Render(a_pDevice, a_pPass);
	});
}

void CObj_Render::Render(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}

void CObj_Render::LateRender(ID3D10Device* a_pDevice)
{
	m_pMat->SetMatrix(::G_N_CBUFFER_WORLD_MATRIX, this->GetMatrix_WorldTrans());

	m_pMat->EnumeratePasses(0, [&](auto a_pPass) -> void
	{
		this->LateRender(a_pDevice, a_pPass);
	});
}

void CObj_Render::LateRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass)
{
	// Do Something
}

void CObj_Render::LateRender(ID3DX10Sprite* a_pXSprite)
{
	// Do Something
}
