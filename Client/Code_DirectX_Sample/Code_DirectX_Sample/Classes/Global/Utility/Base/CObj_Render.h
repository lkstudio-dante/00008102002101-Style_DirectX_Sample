#pragma once

#include "CObj.h"

class CMat;

/**
 * 렌더링 객체
 */
class CObj_Render : public CObj
{
public:			// public 함수

	/** 생성자 */
	CObj_Render(const std::string& a_rPath_Effect);

	/** 재질 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CMat*, Mat, m_pMat, nullptr);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void OnRender(LPDIRECT3DDEVICE9 a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnLateRender(LPDIRECT3DDEVICE9 a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass);

	/** 객체를 그린다 */
	virtual void OnLateRender(LPDIRECT3DDEVICE9 a_pDevice, int a_nIdx_Pass);
};
