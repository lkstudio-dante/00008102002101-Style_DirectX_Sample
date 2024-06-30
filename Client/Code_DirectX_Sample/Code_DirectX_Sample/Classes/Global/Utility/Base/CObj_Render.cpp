#include "CObj_Render.h"
#include "CApp_D3D.h"
#include "../Camera/CCamera.h"
#include "../Manager/CManager_Res.h"

CObj_Render::CObj_Render(const std::string& a_rPath_Effect)
{
	m_pEffect = GET_MANAGER_RES()->GetEffect(a_rPath_Effect);
	m_pCBuffer_WorldMatrix = m_pEffect->GetConstantBufferByName(NAME_WORLD_MATRIX_CBUFFER.c_str())->AsMatrix();
}

void CObj_Render::OnRender(ID3D10Device* a_pDevice)
{
	m_pCBuffer_WorldMatrix->SetMatrix(this->GetMatrix_WorldTrans());

	this->EnumeratePasses([&](ID3D10EffectPass* a_pPass) -> void
	{
		this->OnRender(a_pDevice, a_pPass);
	});
}

void CObj_Render::OnLateRender(ID3D10Device* a_pDevice)
{
	m_pCBuffer_WorldMatrix->SetMatrix(this->GetMatrix_WorldTrans());

	this->EnumeratePasses([&](ID3D10EffectPass* a_pPass) -> void
	{
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

void CObj_Render::EnumeratePasses(const std::function<void(ID3D10EffectPass*)>& a_rCallback)
{
	D3D10_TECHNIQUE_DESC stDesc_Technique;
	m_pEffect->GetTechniqueByIndex(0)->GetDesc(&stDesc_Technique);

	for(int i = 0; i < stDesc_Technique.Passes; ++i)
	{
		auto pPass = m_pEffect->GetTechniqueByIndex(0)->GetPassByIndex(i);
		pPass->Apply(0);

		a_rCallback(pPass);
	}
}
