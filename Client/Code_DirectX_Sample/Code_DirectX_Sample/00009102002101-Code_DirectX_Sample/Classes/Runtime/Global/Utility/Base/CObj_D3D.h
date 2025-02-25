#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "CObj_WinAPI.h"

#include "../Interface/IRenderable_D3D.h"

/**
* Direct 3D 객체
*/
class CObj_D3D : public CObj_WinAPI, public virtual IRenderable_D3D
{
public:

	using IRenderable_D3D::Render;
	using IRenderable_D3D::LateRender;

public:			// IRenderable_D3D

	/** 객체를 그린다 */
	virtual void Render(HDC a_hDC) final override;

	/** 객체를 그린다 */
	virtual void LateRender(HDC a_hDC) final override;

public:			// public 함수

	/** 소멸자 */
	virtual ~CObj_D3D(void) = 0;

public:			// public 접근 함수

	/** 위치를 반환한다 */
	virtual D3DXVECTOR3 GetPos_D3D(void) const;

	/** 비율을 반환한다 */
	virtual D3DXVECTOR3 GetScale_D3D(void) const;

	/** 회전을 반환한다 */
	virtual D3DXVECTOR3 GetRotate_D3D(void) const;

	/** X 축 방향을 반환한다 */
	virtual D3DXVECTOR3 GetVec_Right(void) const;

	/** Y 축 방향을 반환한다 */
	virtual D3DXVECTOR3 GetVec_Up(void) const;

	/** Z 축 방향을 반환한다 */
	virtual D3DXVECTOR3 GetVec_Forward(void) const;

	/** 사원수를 반환한다 */
	virtual D3DXQUATERNION GetQuaternion(void) const;

	/** 이동 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_Translate(void) const;

	/** 비율 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_Scale(void) const;

	/** 회전 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_Rotate(void) const;

	/** 로컬 변환 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_LocalTrans(void) const;

	/** 월드 변환 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_WorldTrans(void) const;

	/** 위치를 반환한다 */
	virtual void SetPos_D3D(const D3DXVECTOR3& a_rstPos);

	/** 비율을 반환한다 */
	virtual void SetScale_D3D(const D3DXVECTOR3& a_rstScale);

	/** 회전을 반환한다 */
	virtual void SetRotate_D3D(const D3DXVECTOR3& a_rstRotate);

private:			// private 접근 함수

	/** 부모 객체 월드 변환 행렬을 반환한다 */
	virtual D3DXMATRIXA16 GetMatrix_ParentWorldTrans(void) const;
};
