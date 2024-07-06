#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IReleasable.h"

class CMat;
class CLoader_SkinningMesh;

/**
 * 리소스 관리자
 */
class CManager_Res : public virtual IReleasable
{
public:

	typedef std::unordered_map<std::string, STInfo_Mesh> T_MapInfos_Mesh;
	typedef std::unordered_map<std::string, STInfo_WaveSnd> T_MapInfos_WaveSnd;
	typedef std::unordered_map<std::string, STInfo_SkinningMesh> T_MapInfos_SkinningMesh;

	typedef std::unordered_map<std::string, CMat*> T_MapMaterials;
	typedef std::unordered_map<std::string, CLoader_SkinningMesh*> T_MapLoaders_SkinningMesh;

	typedef std::unordered_map<std::string, LPDIRECT3DTEXTURE9> T_MapTextures;
	typedef std::unordered_map<std::string, LPD3DXEFFECT> T_MapXEffects;

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

	/** 스키닝 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(T_MapInfos_SkinningMesh, Infos_SkinningMesh, m_oMapInfos_SkinningMesh);

	/** 재질 프로퍼티 */
	GETTER_PROPERTY(T_MapMaterials, Materials, m_oMapMaterials);

	/** 스키닝 메쉬 로더 프로퍼티 */
	GETTER_PROPERTY(T_MapLoaders_SkinningMesh, Loaders_SkinningMesh, m_oMapLoaders_SkinningMesh);

	/** 텍스처 프로퍼티 */
	GETTER_PROPERTY(T_MapTextures, MapTextures, m_oMapTextures);

	/** 이펙트 프로퍼티 */
	GETTER_PROPERTY(T_MapXEffects, XEffects, m_oMapXEffects);

public:			// public 접근 함수

	/** 메쉬 정보를 반환한다 */
	STInfo_Mesh GetInfo_Mesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 웨이브 사운드 정보를 반환한다 */
	STInfo_WaveSnd GetInfo_WaveSnd(const std::string& a_rPath_Snd, bool a_bIsCreate_Auto = true);

	/** 스키닝 메쉬 정보를 반환한다 */
	STInfo_SkinningMesh GetInfo_SkinningMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 재질을 반환한다 */
	CMat* GetMat(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto = true);

	/** 스키닝 메쉬 로더를 반환한다 */
	CLoader_SkinningMesh* GetLoader_SkinningMesh(const std::string& a_rPath_Mesh, bool a_bIsCreate_Auto = true);

	/** 텍스처를 반환한다 */
	LPDIRECT3DTEXTURE9 GetTexture(const std::string& a_rPath_Texture, bool a_bIsCreate_Auto = true);

	/** 이펙트를 반환한다 */
	LPD3DXEFFECT GetXEffect(const std::string& a_rPath_Effect, bool a_bIsCreate_Auto = true);
};
