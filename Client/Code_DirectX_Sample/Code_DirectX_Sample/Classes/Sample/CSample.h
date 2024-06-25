#pragma once

#include "../Global/Define/KDefine+Global.h"
#include "../Global/Utility/Base/CApp_D3D.h"

/**
 * 샘플
 */
class CSample : public CApp_D3D
{
public:			// public 함수

	/** 생성자 */
	CSample(HINSTANCE a_hInst, int a_nOptShow, const SIZE& a_rstSizeWnd);

private:			// private 변수

	ID3DX10Mesh* m_pMesh = nullptr;
};
