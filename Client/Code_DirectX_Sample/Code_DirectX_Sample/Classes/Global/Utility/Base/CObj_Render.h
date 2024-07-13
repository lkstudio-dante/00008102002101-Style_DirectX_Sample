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
	virtual void OnRender(ID3D10Device* a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3D10Device* a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);
};
