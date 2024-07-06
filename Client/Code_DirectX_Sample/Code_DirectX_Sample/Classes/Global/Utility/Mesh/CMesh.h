#pragma once

#include "../Base/CObj_Render.h"

/**
 * 메쉬
 */
class CMesh : public CObj_Render
{
public:			// public 함수

	/** 생성자 */
	CMesh(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect);

	/** 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(STInfo_Mesh, Info_Mesh, m_stInfo_Mesh);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass) override;
};
