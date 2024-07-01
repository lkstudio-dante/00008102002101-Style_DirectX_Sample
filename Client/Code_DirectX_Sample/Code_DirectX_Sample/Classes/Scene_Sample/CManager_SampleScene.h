#pragma once

#include "../Global/Define/KDefine+Global.h"
#include "../Global/Utility/Base/CApp_D3D.h"

class CMesh;
class CMesh_Skeleton;

/**
 * 샘플 씬 관리자
 */
class CManager_SampleScene : public CApp_D3D
{
public:			// IRenderable

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) override;

public:			// public 함수

	/** 생성자 */
	CManager_SampleScene(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	~CManager_SampleScene(void);

	/** 초기화 */
	virtual void LateInit(void) override;

private:			// private 변수

	CMesh* m_pGunShip = nullptr;
	CMesh* m_pElementalist = nullptr;
	CMesh_Skeleton* m_pWitchApprentice = nullptr;
};
