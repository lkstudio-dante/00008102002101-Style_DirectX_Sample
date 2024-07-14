#pragma once

#include "CObj_Render.h"

class CMesh;

/**
 * 디버그 객체
 */
class CObj_Debug : public CObj_Render
{
public:			// public 함수

	/** 생성자 */
	CObj_Debug(const std::string& a_rPath_Effect);

	/** 초기화 */
	virtual void Init(void) override;

	/** 메쉬 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CMesh*, Mesh, m_pMesh, nullptr);

protected:			// protected 팩토리 함수

	/** 메쉬를 생성한다 */
	virtual CMesh* CreateMesh(const std::string& a_rPath_Effect);

private:			// private 변수

	std::string m_oPath_Effect = "";
};
