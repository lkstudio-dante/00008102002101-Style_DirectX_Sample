#pragma once

#include "CObj.h"

/**
 * 렌더링 객체
 */
class CObj_Render : public CObj
{
public:			// public 함수

	/** 생성자 */
	CObj_Render(const std::string& a_rPath_Effect);

	/** 이펙트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10Effect*, Effect, m_pEffect, nullptr);

	/** 월드 행렬 상수 버퍼 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10EffectMatrixVariable*, CBuffer_WorldMatrix, m_pCBuffer_WorldMatrix, nullptr);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void OnRender(ID3D10Device* a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3D10Device* a_pDevice) final override;

	/** 객체를 그린다 */
	virtual void OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);

	/** 객체를 그린다 */
	virtual void OnLateRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);

private:			// private 함수

	/** 패스를 순회한다 */
	void EnumeratePasses(const std::function<void(ID3D10EffectPass*)>& a_rCallback);
};
