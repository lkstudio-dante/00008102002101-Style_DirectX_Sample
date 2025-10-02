#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "CObj_D3D.h"

class CMat;

/**
* 렌더링 객체
*/
class CObj_Render : public CObj_D3D
{
public:			// public 함수

	/** 생성자 */
	CObj_Render(const std::string& a_rPath_Effect);

	/** 초기화 */
	virtual void Init(void) override;

	/** 재질 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(CMat*, Mat, m_pMat, nullptr);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) override;

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);

	/** 객체를 그린다 */
	virtual void LateRender(ID3D10Device* a_pDevice) override;

	/** 객체를 그린다 */
	virtual void LateRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass);

	/** 객체를 그린다 */
	virtual void LateRender(ID3DX10Sprite* a_pXSprite) override;

private:			// private 변수

	std::string m_oPath_Effect = "";
};
