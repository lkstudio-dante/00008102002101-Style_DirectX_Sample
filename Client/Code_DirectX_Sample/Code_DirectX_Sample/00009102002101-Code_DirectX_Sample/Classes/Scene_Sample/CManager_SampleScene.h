#pragma once

#include "../Global/Define/KDefine+Global.h"
#include "Packages/00000302000101-Module_DirectX_Common/Client/Classes/Global/Utility/Base/CApp_D3D.h"

class CGrid;
class CMesh;
class CMesh_Skeletal;

/**
 * 샘플 씬 관리자
 */
class CManager_SampleScene : public CApp_D3D
{
public:			// public 함수

	/** 생성자 */
	CManager_SampleScene(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd);

	/** 소멸자 */
	~CManager_SampleScene(void);

	/** 초기화 */
	virtual void LateInit(void) override;

	/** 상태를 갱신한다 */
	virtual void Update(float a_fTime_Delta) override;

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) override;

private:			// private 변수

	CGrid* m_pGrid = nullptr;
	CMesh* m_pGunShip = nullptr;
	CMesh* m_pElementalist = nullptr;
	CMesh_Skeletal* m_pWitchApprentice = nullptr;
};
