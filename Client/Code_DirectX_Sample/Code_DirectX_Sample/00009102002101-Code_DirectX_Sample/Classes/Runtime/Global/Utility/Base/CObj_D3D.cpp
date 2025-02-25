#include "CObj_D3D.h"
#include "CApp_D3D.h"

#include "../../Access/CAccess+DirectX_Abs.h"

#include "../../Function/CFunc+Cpp_Abs.h"
#include "../../Function/CFunc+DirectX_Abs.h"

CObj_D3D::~CObj_D3D(void)
{
	// Do Something
}

void CObj_D3D::Render(HDC a_hDC)
{
	this->Render(GET_APP_D3D()->GetDevice());
}

void CObj_D3D::LateRender(HDC a_hDC)
{
	this->LateRender(GET_APP_D3D()->GetDevice());
}

D3DXVECTOR3 CObj_D3D::GetPos_D3D(void) const
{
	return CFunc::GLToD3DVec(this->GetPos());
}

D3DXVECTOR3 CObj_D3D::GetScale_D3D(void) const
{
	return CFunc::GLToD3DVec(this->GetScale());
}

D3DXVECTOR3 CObj_D3D::GetRotate_D3D(void) const
{
	return CFunc::GLToD3DVec(this->GetRotate());
}

D3DXVECTOR3 CObj_D3D::GetVec_Right(void) const
{
	auto stVec_Right = CAccess::GetVec_Trans(::G_VEC_WORLD_RIGHT,
		this->GetMatrix_Rotate(), false);

	return *D3DXVec3Normalize(&stVec_Right, &stVec_Right);
}

D3DXVECTOR3 CObj_D3D::GetVec_Up(void) const
{
	auto stVec_Up = CAccess::GetVec_Trans(::G_VEC_WORLD_UP,
		this->GetMatrix_Rotate(), false);

	return *D3DXVec3Normalize(&stVec_Up, &stVec_Up);
}

D3DXVECTOR3 CObj_D3D::GetVec_Forward(void) const
{
	auto stVec_Forward = CAccess::GetVec_Trans(::G_VEC_WORLD_FORWARD,
		this->GetMatrix_Rotate(), false);

	return *D3DXVec3Normalize(&stVec_Forward, &stVec_Forward);
}

D3DXQUATERNION CObj_D3D::GetQuaternion(void) const
{
	return CAccess::GetQuaternion(this->GetRotate_D3D());
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_Translate(void) const
{
	return CAccess::GetMatrix_Translate(this->GetPos_D3D());
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_Scale(void) const
{
	return CAccess::GetMatrix_Scale(this->GetScale_D3D());
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_Rotate(void) const
{
	return CAccess::GetMatrix_Rotate(this->GetRotate_D3D());
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_LocalTrans(void) const
{
	return CAccess::GetMatrix_Trans(this->GetPos_D3D(),
		this->GetScale_D3D(), this->GetRotate_D3D());
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_WorldTrans(void) const
{
	return this->GetMatrix_LocalTrans() * this->GetMatrix_ParentWorldTrans();
}

void CObj_D3D::SetPos_D3D(const D3DXVECTOR3& a_rstPos)
{
	this->SetPos(CFunc::D3DToGLVec(a_rstPos));
}

void CObj_D3D::SetScale_D3D(const D3DXVECTOR3& a_rstScale)
{
	this->SetScale(CFunc::D3DToGLVec(a_rstScale));
}

void CObj_D3D::SetRotate_D3D(const D3DXVECTOR3& a_rstRotate)
{
	this->SetRotate(CFunc::D3DToGLVec(a_rstRotate));
}

D3DXMATRIXA16 CObj_D3D::GetMatrix_ParentWorldTrans(void) const
{
	// 부모 객체가 존재 할 경우
	if(auto pParent = dynamic_cast<CObj_D3D*>(this->GetParent()))
	{
		return pParent->GetMatrix_WorldTrans();
	}

	D3DXMATRIXA16 stMatrix_ParentTrans;
	D3DXMatrixIdentity(&stMatrix_ParentTrans);

	return stMatrix_ParentTrans;
}
