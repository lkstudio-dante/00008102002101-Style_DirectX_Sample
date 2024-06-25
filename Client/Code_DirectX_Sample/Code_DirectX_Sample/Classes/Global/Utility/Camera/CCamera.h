#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 카메라
 */
class CCamera
{
public:			// public 함수

	/** 생성자 */
	CCamera(void);

	/** FOV 프로퍼티 */
	GETTER_SETTER_PROPERTY_WITH_INIT(float, FOV, m_fFOV, 0.0f);

	/** 뷰포트 프로퍼티 */
	GETTER_SETTER_PROPERTY(D3D10_VIEWPORT, Viewport, m_stViewport);

	/** 뷰 행렬 프로퍼티 */
	GETTER_SETTER_PROPERTY(D3DXMATRIX, MatrixView, m_stMatrixView);

	/** 투영 행렬 프로퍼티 */
	GETTER_SETTER_PROPERTY(D3DXMATRIX, MatrixProjection, m_stMatrixProjection);

public:			// public 접근 함수

	/** 거리를 반환한다 */
	float GetDistance(void) const;

	/** 변환 행렬을 반환한다 */
	D3DXMATRIXA16 GetMatrixTrans(void) const;
};
