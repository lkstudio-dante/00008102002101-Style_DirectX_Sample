#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Base/CObj_Render.h"

/**
 * 스키닝 메쉬
 */
class CMesh_Skinning : public CObj_Render
{
public:			// public 함수

	/** 생성자 */
	CMesh_Skinning(const std::string& a_rPath_Mesh, const std::string& a_rPath_Effect);

	/** 스키닝 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(STInfo_SkinningMesh, Info_SkinningMesh, m_stInfo_SkinningMesh);

protected:			// protected 함수

	/** 상태를 갱신한다 */
	virtual void OnUpdate(float a_fTime_Delta) override;

	/** 객체를 그린다 */
	virtual void OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass) override;
};
