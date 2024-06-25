#include "CManager_Res.h"
#include "../Base/CApp_D3D.h"

/** 리소스를 제거한다 */
template <typename K, typename V>
static void ReleaseResources(std::unordered_map<K, V>& a_rMapResources)
{
	for(auto& rstValType : a_rMapResources)
	{
		SAFE_RELEASE(rstValType.second);
	}
}

CManager_Res::CManager_Res(void)
{
	// Do Something
}

CManager_Res::~CManager_Res(void)
{
	this->Release(true);
}

void CManager_Res::Release(bool a_bIsDestroy)
{
	ReleaseResources(m_oMapEffects);
	ReleaseResources(m_oMapViewsSR);
}

void CManager_Res::Init(void)
{
	// Do Something
}

ID3D10Effect* CManager_Res::GetEffect(const std::string& a_rPathEffect, bool a_bIsCreateAuto)
{
	// 이펙트가 없을 경우
	if(a_bIsCreateAuto && m_oMapEffects.find(a_rPathEffect) == m_oMapEffects.end())
	{
		ID3D10Blob* pError = nullptr;
		ID3D10Effect* pEffect = nullptr;

		D3DX10CreateEffectFromFileA(a_rPathEffect.c_str(),
			nullptr, nullptr, VER_EFFECT.c_str(), D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, GET_APP_D3D()->GetDevice(), nullptr, nullptr, &pEffect, &pError, nullptr);

		// 에러가 존재 할 경우
		if(pError != nullptr)
		{
			printf("CManager_Res.GetEffect: %s\n", (char*)pError->GetBufferPointer());
		}

		m_oMapEffects.insert(decltype(m_oMapEffects)::value_type(a_rPathEffect, pEffect));
	}

	return m_oMapEffects[a_rPathEffect];
}

ID3D10ShaderResourceView* CManager_Res::GetViewSR(const std::string& a_rPathTexture, bool a_bIsCreateAuto)
{
	// 쉐이더 리소스 뷰가 없을 경우
	if(a_bIsCreateAuto && m_oMapViewsSR.find(a_rPathTexture) == m_oMapViewsSR.end())
	{
		ID3D10ShaderResourceView* pViewSR = nullptr;

		D3DX10CreateShaderResourceViewFromFileA(GET_APP_D3D()->GetDevice(),
			a_rPathTexture.c_str(), nullptr, nullptr, &pViewSR, nullptr);

		m_oMapViewsSR.insert(decltype(m_oMapViewsSR)::value_type(a_rPathTexture, pViewSR));
	}

	return m_oMapViewsSR[a_rPathTexture];
}
