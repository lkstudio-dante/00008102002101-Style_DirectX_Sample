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

	/** 메쉬 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3DX10Mesh*, Mesh, m_pMesh, nullptr);

	/** 디퓨즈 맵 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(ID3D10EffectShaderResourceVariable*, CBuffer_DiffuseMap, m_pCBuffer_DiffuseMap, nullptr);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void OnRender(ID3D10Device* a_pDevice, ID3D10EffectPass* a_pPass) override;

private:			// private 변수

	STInfo_Mesh m_stInfo_Mesh;
};
