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
	this->Release(true);
}

void CObj::Init(void)
{
	// Do Something
}

void CObj::Release(bool a_bIsDestroy)
{
	// 제거 모드 일 경우
	if(a_bIsDestroy || m_pParent == nullptr)
	{
		return;
	}

	for(auto pChild : m_oVectorChildren)
	{
		SAFE_DEL(pChild);
	}

	m_pParent->RemoveChild(this);
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

void CObj::Render(ID3D10Device* a_pDevice)
{
	this->OnRender(a_pDevice);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->Render(a_pDevice);
	}
}

void CObj::LateRender(ID3D10Device* a_pDevice)
{
	this->OnLateRender(a_pDevice);

	for(auto pChild : m_oVectorChildren)
	{
		pChild->LateRender(a_pDevice);
	}
}

void CObj::LateRender(ID3DX10Sprite* a_pXSprite)
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
	auto stVec_Right = Access::GetVec_Trans(VEC_WORLD_RIGHT, this->GetMatrix_Rotate(), false);
	return *D3DXVec3Normalize(&stVec_Right, &stVec_Right);
}

D3DXVECTOR3 CObj::GetVec_Up(void) const
{
	auto stVec_Up = Access::GetVec_Trans(VEC_WORLD_UP, this->GetMatrix_Rotate(), false);
	return *D3DXVec3Normalize(&stVec_Up, &stVec_Up);
}

D3DXVECTOR3 CObj::GetVec_Forward(void) const
{
	auto stVec_Forward = Access::GetVec_Trans(VEC_WORLD_FORWARD, this->GetMatrix_Rotate(), false);
	return *D3DXVec3Normalize(&stVec_Forward, &stVec_Forward);
}

D3DXQUATERNION CObj::GetQuaternion(void) const
{
	return Access::GetQuaternion(m_stRotate);
}

D3DXMATRIXA16 CObj::GetMatrix_Pos(void) const
{
	return Access::GetMatrix_Pos(m_stPos);
}

D3DXMATRIXA16 CObj::GetMatrix_Scale(void) const
{
	return Access::GetMatrix_Scale(m_stScale);
}

D3DXMATRIXA16 CObj::GetMatrix_Rotate(void) const
{
	return Access::GetMatrix_Rotate(m_stRotate);
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

void CObj::OnRender(ID3D10Device* a_pDevice)
{
	// Do Something
}

void CObj::OnLateRender(ID3D10Device* a_pDevice)
{
	// Do Something
}

void CObj::OnLateRender(ID3DX10Sprite* a_pXSprite)
{
	// Do Something
}

D3DXMATRIXA16 CObj::GetMatrix_ParentWorldTrans(void) const
{
	D3DXMATRIXA16 stMatrix_ParentTrans;
	D3DXMatrixIdentity(&stMatrix_ParentTrans);

	return (m_pParent != nullptr) ? m_pParent->GetMatrix_WorldTrans() : stMatrix_ParentTrans;
}
