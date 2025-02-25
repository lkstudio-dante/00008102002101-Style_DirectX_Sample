#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "../Base/CObj.h"

#include "../Interface/IRenderable_WinAPI.h"

/**
* 윈도우즈 API 객체
*/
class CObj_WinAPI : public CObj, public virtual IRenderable_WinAPI
{
public:

	using IUpdateable::Update;
	using IUpdateable::LateUpdate;

	using IRenderable_WinAPI::Render;
	using IRenderable_WinAPI::LateRender;

public:			// public 함수

	/** 생성자 */
	CObj_WinAPI(void);

	/** 소멸자 */
	virtual ~CObj_WinAPI(void) = 0;

	/** 객체를 제거한다 */
	virtual void Destroy(void) override;

	/** 상태를 갱신한다 */
	virtual void Update(void) final override;

	/** 상태를 갱신한다 */
	virtual void LateUpdate(void) final override;

	/** 객체를 그린다 */
	virtual void Render(void) final override;

	/** 객체를 그린다 */
	virtual void LateRender(void) final override;

	/** 자식 객체를 추가한다 */
	virtual void AddChild(CObj_WinAPI* a_pChild);

	/** 자식 객체를 제거한다 */
	virtual void RemoveChild(CObj_WinAPI* a_pChild);

	/** 위치 프로퍼티 */
	GETTER_SETTER_PROPERTY(glm::vec3, Pos, m_stPos);

	/** 비율 프로퍼티 */
	GETTER_SETTER_PROPERTY(glm::vec3, Scale, m_stScale);

	/** 회전 프로퍼티 */
	GETTER_SETTER_PROPERTY(glm::vec3, Rotate, m_stRotate);

	/** 부모 객체 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(CObj_WinAPI*, Parent, m_pParent, nullptr);

public:			// public 접근 함수

	/** 자식을 반환한다 */
	CObj_WinAPI* GetChild(int a_nIdx);

	/** 자식을 반환한다 */
	std::vector<CObj_WinAPI*>& GetChildren(void);

private:			// private 변수

	std::vector<CObj_WinAPI*> m_oVectorChildren;
};
