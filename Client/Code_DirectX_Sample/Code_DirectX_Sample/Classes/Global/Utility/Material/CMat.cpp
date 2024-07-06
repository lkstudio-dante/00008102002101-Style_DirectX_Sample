#include "CMat.h"
#include "../Manager/CManager_Res.h"

CMat::CMat(const std::string& a_rPath_Effect)
{
	m_pXEffect = GET_MANAGER_RES()->GetXEffect(a_rPath_Effect);
}

void CMat::EnumeratePasses(int a_nIdx_Technique, const std::function<void(int)>& a_rCallback)
{
	auto hTechnique = m_pXEffect->GetTechnique(a_nIdx_Technique);
	m_pXEffect->SetTechnique(hTechnique);

	UINT nNumPasses = 0;
	m_pXEffect->Begin(&nNumPasses, 0);

	for(int i = 0; i < nNumPasses; ++i)
	{
		m_pXEffect->BeginPass(i);
		a_rCallback(i);

		m_pXEffect->EndPass();
	}

	m_pXEffect->End();
}

void CMat::SetColor(const std::string& a_rKey, const D3DXCOLOR& a_rstColor)
{
	D3DXVECTOR4 stVec(a_rstColor.a, a_rstColor.g, a_rstColor.b, a_rstColor.a);
	m_pXEffect->SetVector(a_rKey.c_str(), &stVec);
}

void CMat::SetMatrix(const std::string& a_rKey, const D3DXMATRIXA16& a_rstMatrix)
{
	m_pXEffect->SetMatrix(a_rKey.c_str(), &a_rstMatrix);
}

void CMat::SetTexture(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture)
{
	m_pXEffect->SetTexture(a_rKey.c_str(), a_pTexture);
}

void CMat::SetTexture_Cube(const std::string& a_rKey, LPDIRECT3DCUBETEXTURE9 a_pTexture_Cube)
{
	m_pXEffect->SetTexture(a_rKey.c_str(), a_pTexture_Cube);
}
