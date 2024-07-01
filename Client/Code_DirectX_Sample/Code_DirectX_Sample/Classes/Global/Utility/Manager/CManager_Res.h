#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IReleasable.h"

class CMat;
class CLoader_SkeletonMesh;

/**
 * 리소스 관리자
 */
class CManager_Res : public virtual IReleasable
{
public:

	typedef std::unordered_map<std::string, STInfo_Mesh> T_MapInfos_Mesh;
	typedef std::unordered_map<std::string, STInfo_WaveSnd> T_MapInfos_WaveSnd;
	typedef std::unordered_map<std::string, STInfo_SkeletonMesh> T_MapInfos_SkeletonMesh;

	typedef std::unordered_map<std::string, CMat*> T_MapMaterials;
	typedef std::unordered_map<std::string, CLoader_SkeletonMesh*> T_MapLoaders_SkeletonMesh;

	typedef std::unordered_map<std::string, ID3D10Effect*> T_MapEffects;
	typedef std::unordered_map<std::string, ID3D10InputLayout*> T_MapInputLayouts;
	typedef std::unordered_map<std::string, ID3D10ShaderResourceView*> T_MapViews_SR;

public:			// IReleasable

	/** 해제한다 */
	virtual void Release(bool a_bIsDestroy = false) override;

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Res);

	/** 초기화 */
	virtual void Init(void);

	/** 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(T_MapInfos_Mesh, Infos_Mesh, m_oMapInfos_Mesh);

	/** 웨이브 사운드 정보 프로퍼티 */
	GETTER_PROPERTY(T_MapInfos_WaveSnd, Infos_WaveSnd, m_oMapInfos_WaveSnd);

	/** 스켈레톤 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(T_MapInfos_SkeletonMesh, Infos_SkeletonMesh, m_oMapInfos_SkeletonMesh);

	/** 재질 프로퍼티 */
	GETTER_PROPERTY(T_MapMaterials, Materials, m_oMapMaterials);

	/** 스켈레톤 메쉬 로더 프로퍼티 */
	GETTER_PROPERTY(T_MapLoaders_SkeletonMesh, Loaders_SkeletonMesh, m_oMapLoaders_SkeletonMesh);

	/** 이펙트 프로퍼티 */
	GETTER_PROPERTY(T_MapEffects, Effects, m_oMapEffects);

	/** 입력 레이아웃 프로퍼티 */
	GETTER_PROPERTY(T_MapInputLayouts, InputLayouts, m_oMapInputLayouts);

	/** 쉐이더 리소스 뷰 프로퍼티 */
	GETTER_PROPERTY(T_MapViews_SR, Views_SR, m_oMapViews_SR);

public:			// public 접근 함수

	/** 메쉬 정보를 반환한다 */
	STInfo_Mesh GetInfo_Mesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 웨이브 사운드 정보를 반환한다 */
	STInfo_WaveSnd GetInfo_WaveSnd(const std::string& a_rPath_Snd, bool a_bIsCreate_Auto = true);

	/** 스켈레톤 메쉬 정보를 반환한다 */
	STInfo_SkeletonMesh GetInfo_SkeletonMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 재질을 반환한다 */
	CMat* GetMat(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto = true);

	/** 스켈레톤 메쉬 로더를 반환한다 */
	CLoader_SkeletonMesh* GetLoader_SkeletonMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 이펙트를 반환한다 */
	ID3D10Effect* GetEffect(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto = true);
	
	/** 입력 레이아웃을 반환한다 */
	ID3D10InputLayout* GetInputLayout(ID3DX10Mesh* a_pXMesh, const std::string& a_rPath_Effect, bool a_bIsCreate_Auto = true);

	/** 쉐이더 리소스 뷰를 반환한다 */
	ID3D10ShaderResourceView* GetView_SR(const std::string& a_rPath_Texture, bool a_bIsCreate_Auto = true);
};
