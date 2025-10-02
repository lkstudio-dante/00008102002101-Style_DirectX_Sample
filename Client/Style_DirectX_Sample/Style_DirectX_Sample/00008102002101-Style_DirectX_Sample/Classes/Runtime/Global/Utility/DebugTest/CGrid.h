#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "../Base/CObj_Debug.h"

class CMesh;

/**
* 그리드
*/
class CGrid : public CObj_Debug
{
public:			// public 함수

	/** 초기화 */
	CGrid(const std::string& a_rPath_Effect, const SIZE& a_rstSize);

protected:			// protected 함수

	/** 객체를 그린다 */
	virtual void Render(ID3D10Device* a_pDevice) override;

protected:			// protected 팩토리 함수

	/** 메쉬를 생성한다 */
	virtual CMesh* CreateMesh(const std::string& a_rPath_Effect) override;

private:			// private 변수

	SIZE m_stSize;
};
