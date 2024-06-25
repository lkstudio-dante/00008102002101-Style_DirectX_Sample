#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IReleasable.h"

/**
 * 리소스 관리자
 */
class CManager_Res : public virtual IReleasable
{
public:			// IReleasable

	/** 해제한다 */
	virtual void Release(bool a_bIsDestroy = false) override;

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Res);

	/** 초기화 */
	virtual void Init(void);

public:			// public 접근 함수

	/** 이펙트를 반환한다 */
	ID3D10Effect* GetEffect(const std::string& a_rPathEffect, bool a_bIsCreateAuto = true);

	/** 쉐이더 리소스 뷰를 반환한다 */
	ID3D10ShaderResourceView* GetViewSR(const std::string& a_rPathTexture, bool a_bIsCreateAuto = true);

private:			// private 변수

	std::unordered_map<std::string, ID3D10Effect*> m_oMapEffects;
	std::unordered_map<std::string, ID3D10ShaderResourceView*> m_oMapViewsSR;
};
