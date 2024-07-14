#include "CMat.h"
#include "../../Access/Access+Global.h"
#include "../Manager/CManager_Res.h"

CMat::CMat(const std::string& a_rPath_Effect)
{
	m_pEffect = GET_MANAGER_RES()->GetEffect(a_rPath_Effect);
}

void CMat::EnumeratePasses(int a_nIdx_Technique, const std::function<void(ID3D10EffectPass*)>& a_rCallback)
{
	D3D10_TECHNIQUE_DESC stDesc_Technique;
	m_pEffect->GetTechniqueByIndex(a_nIdx_Technique)->GetDesc(&stDesc_Technique);

	for(int i = 0; i < stDesc_Technique.Passes; ++i)
	{
		auto pPass = m_pEffect->GetTechniqueByIndex(a_nIdx_Technique)->GetPassByIndex(i);
		pPass->Apply(0);

		a_rCallback(pPass);
	}
}

void CMat::SetColor(const std::string& a_rKey, const D3DXCOLOR& a_rstColor)
{
	D3DXVECTOR4 stVec(a_rstColor.r, a_rstColor.g, a_rstColor.b, a_rstColor.a);
	this->SetVec(a_rKey, stVec);
}

void CMat::SetVec(const std::string& a_rKey, const D3DXVECTOR4& a_rstVec)
{
	auto pCBuffer_Vec = m_pEffect->GetConstantBufferByName(a_rKey.c_str())->AsVector();
	pCBuffer_Vec->SetFloatVector(const_cast<D3DXVECTOR4&>(a_rstVec));
}

void CMat::SetMatrix(const std::string& a_rKey, const D3DXMATRIXA16& a_rstMatrix)
{
	auto pCBuffer_Matrix = m_pEffect->GetConstantBufferByName(a_rKey.c_str())->AsMatrix();
	pCBuffer_Matrix->SetMatrix(const_cast<D3DXMATRIXA16&>(a_rstMatrix));
}

void CMat::SetView_SR(const std::string& a_rKey, ID3D10ShaderResourceView* a_pView_SR)
{
	auto pCBuffer_SRView = m_pEffect->GetConstantBufferByName(a_rKey.c_str())->AsShaderResource();
	pCBuffer_SRView->SetResource(a_pView_SR);
}
