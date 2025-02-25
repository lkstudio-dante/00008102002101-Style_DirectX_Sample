#include "CObj_WinAPI.h"
#include "CApp_WinAPI.h"

#include "../../Access/CAccess+Cpp_Abs.h"
#include "../../Function/CFunc+Cpp_Abs.h"

#include "../Manager/CManager_Time.h"

CObj_WinAPI::CObj_WinAPI(void)
{
	ZeroMemory(&m_stPos, sizeof(m_stPos));
	ZeroMemory(&m_stScale, sizeof(m_stScale));
}

CObj_WinAPI::~CObj_WinAPI(void)
{
	// Do Something
}

void CObj_WinAPI::Destroy(void)
{
	// 부모 객체가 존재 할 경우
	if(m_pParent != nullptr)
	{
		m_pParent->RemoveChild(this);
	}

	CFunc::DeleteResources(m_oVectorChildren);
}

void CObj_WinAPI::Update(void)
{
	this->Update(GET_MANAGER_TIME()->GetTime_Delta());

	for(auto pObj_Child : m_oVectorChildren)
	{
		pObj_Child->Update();
	}
}

void CObj_WinAPI::LateUpdate(void)
{
	this->LateUpdate(GET_MANAGER_TIME()->GetTime_Delta());

	for(auto pObj_Child : m_oVectorChildren)
	{
		pObj_Child->LateUpdate();
	}
}

void CObj_WinAPI::Render()
{
	this->Render(GET_APP_WIN_API()->GetHandle_DC());

	for(auto pObj_Child : m_oVectorChildren)
	{
		pObj_Child->Render();
	}
}

void CObj_WinAPI::LateRender()
{
	this->LateRender(GET_APP_WIN_API()->GetHandle_DC());

	for(auto pObj_Child : m_oVectorChildren)
	{
		pObj_Child->LateRender();
	}
}

void CObj_WinAPI::AddChild(CObj_WinAPI* a_pChild)
{
	assert(a_pChild != nullptr);
	auto oResult = std::find(m_oVectorChildren.begin(), m_oVectorChildren.end(), a_pChild);

	// 객체 추가가 불가능 할 경우
	if(oResult != m_oVectorChildren.end() || a_pChild->m_pParent != nullptr)
	{
		return;
	}

	a_pChild->m_pParent = this;
	m_oVectorChildren.push_back(a_pChild);
}

void CObj_WinAPI::RemoveChild(CObj_WinAPI * a_pChild)
{
	assert(a_pChild != nullptr);
	auto oResult = std::find(m_oVectorChildren.begin(), m_oVectorChildren.end(), a_pChild);

	// 객체 제거가 불가능 할 경우
	if(oResult == m_oVectorChildren.end())
	{
		return;
	}

	a_pChild->m_pParent = nullptr;
	m_oVectorChildren.erase(oResult);
}

CObj_WinAPI* CObj_WinAPI::GetChild(int a_nIdx)
{
	return CAccess::GetVal<CObj_WinAPI*>(m_oVectorChildren, a_nIdx, nullptr);
}

std::vector<CObj_WinAPI*>& CObj_WinAPI::GetChildren(void)
{
	return m_oVectorChildren;
}
