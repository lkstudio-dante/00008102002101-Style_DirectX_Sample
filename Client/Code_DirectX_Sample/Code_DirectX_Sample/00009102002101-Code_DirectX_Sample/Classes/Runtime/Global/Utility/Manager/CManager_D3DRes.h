#pragma once

#include "../../Define/KCDefine+DirectX_Abs.h"
#include "../Base/CObj.h"

class CMat;
class CLoader_SkeletalMesh;

/**
* Direct 3D 리소스 관리자
*/
class CManager_D3DRes : public CObj
{
public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_D3DRes);

	/** 리소스를 해제한다 */
	virtual void Release(void) override;

	/** 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, STInfo_Mesh), 
		Infos_Mesh, m_oMapInfos_Mesh);

	/** 스켈레톤 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, STInfo_SkeletalMesh), 
		Infos_SkeletalMesh, m_oMapInfos_SkeletalMesh);

	/** 재질 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, CMat*), 
		Materials, m_oMapMaterials);

	/** 스켈레톤 메쉬 로더 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, CLoader_SkeletalMesh*), 
		Loaders_SkeletalMesh, m_oMapLoaders_SkeletalMesh);

	/** 이펙트 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, ID3D10Effect*), 
		Effects, m_oMapEffects);

	/** 입력 레이아웃 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, ID3D10InputLayout*), 
		InputLayouts, m_oMapInputLayouts);

	/** 쉐이더 리소스 뷰 프로퍼티 */
	GETTER_PROPERTY(STD_UNORDERED_MAP(std::string, ID3D10ShaderResourceView*), 
		MapViews_SR, m_oMapViews_SR);

public:			// public 접근 함수

	/** 메쉬 정보를 반환한다 */
	STInfo_Mesh GetInfo_Mesh(const std::string& a_rKey, 
		bool a_bIsCreate_Auto = true);

	/** 스켈레톤 메쉬 정보를 반환한다 */
	STInfo_SkeletalMesh GetInfo_SkeletalMesh(const std::string& a_rKey, 
		bool a_bIsCreate_Auto = true);

	/** 재질을 반환한다 */
	CMat* GetMat(const std::string& a_rKey, bool a_bIsCreate_Auto = true);

	/** 스켈레톤 메쉬 로더를 반환한다 */
	CLoader_SkeletalMesh* GetLoader_SkeletalMesh(const std::string& a_rKey, 
		bool a_bIsCreate_Auto = true);

	/** 이펙트를 반환한다 */
	ID3D10Effect* GetEffect(const std::string& a_rKey, bool a_bIsCreate_Auto = true);

	/** 입력 레이아웃을 반환한다 */
	ID3D10InputLayout* GetInputLayout(const std::string& a_rKey, 
		bool a_bIsCreate_Auto = true);

	/** 쉐이더 리소스 뷰를 반환한다 */
	ID3D10ShaderResourceView* GetView_SR(const std::string& a_rKey, 
		bool a_bIsCreate_Auto = true);
};
