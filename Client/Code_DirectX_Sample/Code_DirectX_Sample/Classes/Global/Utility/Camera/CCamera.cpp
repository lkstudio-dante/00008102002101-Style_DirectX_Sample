#include "CCamera.h"
#include "../Base/CApp_Wnd.h"

CCamera::CCamera(void)
{
	ZeroMemory(&m_stViewport, sizeof(m_stViewport));

	D3DXMatrixIdentity(&m_stMatrixView);
	D3DXMatrixIdentity(&m_stMatrixProjection);
}

float CCamera::GetDistance(void) const
{
	float fFOV = D3DXToRadian(m_fFOV / 2.0f);
	return (GET_APP_WND()->GetSizeWnd().cy / 2.0f) / tan(fFOV);
}

D3DXMATRIXA16 CCamera::GetMatrixTrans(void) const
{
	return m_stMatrixView * m_stMatrixProjection;
}
