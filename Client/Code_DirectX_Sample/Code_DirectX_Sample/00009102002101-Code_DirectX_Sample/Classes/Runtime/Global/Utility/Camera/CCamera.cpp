#include "CCamera.h"
#include "../Base/CApp_D3D.h"

CCamera::CCamera(void)
{
	ZeroMemory(&m_stViewport, sizeof(m_stViewport));
}

float CCamera::GetDistance(void) const
{
	float fFOV = D3DXToRadian(m_fFOV / 2.0f);
	return (GET_APP_WIN_API()->GetSize_Wnd().cy / 2.0f) / tan(fFOV);
}

D3DXMATRIXA16 CCamera::GetMatrix_View(void) const
{
	auto stMatrix_Translate = this->GetMatrix_Translate();
	auto stMatrix_Rotate = this->GetMatrix_Rotate();

	return *D3DXMatrixInverse(&stMatrix_Translate, nullptr, &stMatrix_Translate) *
		*D3DXMatrixInverse(&stMatrix_Rotate, nullptr, &stMatrix_Rotate);
}

D3DXMATRIXA16 CCamera::GetMatrix_Projection(void) const
{
	D3DXMATRIXA16 stMatrix_Projection;

	D3DXMatrixPerspectiveFovLH(&stMatrix_Projection,
		D3DXToRadian(this->GetFOV()), GET_APP_WIN_API()->GetSize_Wnd().cx / (float)GET_APP_WIN_API()->GetSize_Wnd().cy, this->GetPlane_Near(), this->GetPlane_Far());

	return stMatrix_Projection;
}
