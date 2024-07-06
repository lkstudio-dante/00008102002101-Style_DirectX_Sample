#include "CObj.h"
#include "../../Access/Access+Global.h"

CObj::CObj(void)
	:
	m_stScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
{
	ZeroMemory(&m_stPos, sizeof(m_stPos));
	ZeroMemory(&m_stRotate, sizeof(m_stRotate));
}

CObj::~CObj(void)
{
	// Do Something
}

void CObj::Update(float a_fTime_Delta)
{
	this->OnUpdate(a_fTime_Delta);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->Update(a_fTime_Delta);
	}
}

void CObj::LateUpdate(float a_fTime_Delta)
{
	this->OnLateUpdate(a_fTime_Delta);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->LateUpdate(a_fTime_Delta);
	}
}

void CObj::Render(LPDIRECT3DDEVICE9 a_pDevice)
{
	this->OnRender(a_pDevice);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->Render(a_pDevice);
	}
}

void CObj::LateRender(LPDIRECT3DDEVICE9 a_pDevice)
{
	this->OnLateRender(a_pDevice);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->LateRender(a_pDevice);
	}
}

void CObj::LateRender(LPD3DXSPRITE a_pXSprite)
{
	this->OnLateRender(a_pXSprite);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->LateRender(a_pXSprite);
	}
}

void CObj::AddChild(CObj* a_pChild)
{
	assert(a_pChild != nullptr);
	auto oIter = std::find(m_oVectorChildren.begin(), m_oVectorChildren.end(), a_pChild);

	// 객체 추가가 불가능 할 경우
	if(oIter != m_oVectorChildren.end() || a_pChild->m_pParent != nullptr)
	{
		return;
	}

	a_pChild->m_pParent = this;
	m_oVectorChildren.push_back(a_pChild);
}

void CObj::RemoveChild(CObj* a_pChild)
{
	assert(a_pChild != nullptr);
	auto oIter = std::find(m_oVectorChildren.begin(), m_oVectorChildren.end(), a_pChild);

	// 객체 제거가 불가능 할 경우
	if(oIter == m_oVectorChildren.end())
	{
		return;
	}

	a_pChild->m_pParent = nullptr;
	m_oVectorChildren.erase(oIter);
}

D3DXVECTOR3 CObj::GetVec_Right(void) const
{
	return Access::GetVec_Trans(VEC_WORLD_RIGHT, this->GetMatrix_LocalTrans(), false);
}

D3DXVECTOR3 CObj::GetVec_Up(void) const
{
	return Access::GetVec_Trans(VEC_WORLD_UP, this->GetMatrix_LocalTrans(), false);
}

D3DXVECTOR3 CObj::GetVec_Forward(void) const
{
	return Access::GetVec_Trans(VEC_WORLD_FORWARD, this->GetMatrix_LocalTrans(), false);
}

D3DXMATRIXA16 CObj::GetMatrix_LocalTrans(void) const
{
	return Access::GetMatrix_Trans(m_stPos, m_stScale, m_stRotate);
}

D3DXMATRIXA16 CObj::GetMatrix_WorldTrans(void) const
{
	return this->GetMatrix_LocalTrans() * this->GetMatrix_ParentWorldTrans();
}

void CObj::OnUpdate(float a_fTime_Delta)
{
	// Do Something
}

void CObj::OnLateUpdate(float a_fTime_Delta)
{
	// Do Something
}

void CObj::OnRender(LPDIRECT3DDEVICE9 a_pDevice)
{
	// Do Something
}

void CObj::OnLateRender(LPDIRECT3DDEVICE9 a_pDevice)
{
	// Do Something
}

void CObj::OnLateRender(LPD3DXSPRITE a_pXSprite)
{
	// Do Something
}

D3DXMATRIXA16 CObj::GetMatrix_ParentWorldTrans(void) const
{
	D3DXMATRIXA16 stMatrix_ParentTrans;
	D3DXMatrixIdentity(&stMatrix_ParentTrans);

	return (m_pParent != nullptr) ? m_pParent->GetMatrix_WorldTrans() : stMatrix_ParentTrans;
}
