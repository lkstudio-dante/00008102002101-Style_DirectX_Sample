#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 재질
 */
class CMat
{ 
public:			// public 함수

	/** 생성자 */
	CMat(const std::string& a_rPath_Effect);

	/** 패스를 순회한다 */
	void EnumeratePasses(int a_nIdx_Technique, const std::function<void(int)>& a_rCallback);

	/** 이펙트 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPD3DXEFFECT, XEffect, m_pXEffect, nullptr);

public:			// public 접근 함수

	/** 색상을 변경한다 */
	void SetColor(const std::string& a_rKey, const D3DXCOLOR& a_rstColor);

	/** 행렬을 변경한다 */
	void SetMatrix(const std::string& a_rKey, const D3DXMATRIXA16& a_rstMatrix);

	/** 텍스처를 변경한다 */
	void SetTexture(const std::string& a_rKey, LPDIRECT3DTEXTURE9 a_pTexture);

	/** 큐브 텍스처를 변경한다 */
	void SetTexture_Cube(const std::string& a_rKey, LPDIRECT3DCUBETEXTURE9 a_pTexture_Cube);
};
