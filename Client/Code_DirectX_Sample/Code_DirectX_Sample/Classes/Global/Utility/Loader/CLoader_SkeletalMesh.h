#pragma once

#include "../../Define/KDefine+Global.h"

/**
 * 스켈레톤 메쉬 로더
 */
class CLoader_SkeletalMesh : public ID3DXAllocateHierarchy
{
public:			// ID3DXAllocateHierarchy

	/** 프레임을 생성한다 */
	virtual HRESULT STDMETHODCALLTYPE CreateFrame(LPCSTR a_pszName, LPD3DXFRAME* a_pstOutXFrame) override;

	/** 메쉬 컨테이너를 생성한다 */
	virtual HRESULT STDMETHODCALLTYPE CreateMeshContainer(LPCSTR a_pszName,
		const D3DXMESHDATA* a_pstXData_Mesh, const D3DXMATERIAL* a_pstXMat, const D3DXEFFECTINSTANCE* a_pstXInst_Effect, DWORD a_nNumMaterials, const DWORD* a_pnAdjacency, LPD3DXSKININFO a_pstXInfo_Skin, LPD3DXMESHCONTAINER* a_pstOutXContainer_Mesh) override;

	/** 프레임을 제거한다 */
	virtual HRESULT STDMETHODCALLTYPE DestroyFrame(LPD3DXFRAME a_pstXFrame) override;

	/** 메쉬 컨테이너를 제거한다 */
	virtual HRESULT STDMETHODCALLTYPE DestroyMeshContainer(LPD3DXMESHCONTAINER a_pstXContainer_Mesh) override;

public:			// public 함수

	/** 생성자 */
	CLoader_SkeletalMesh(const std::string& a_rPath_Mesh);

	/** 스켈레톤 메쉬 정보 프로퍼티 */
	GETTER_PROPERTY(STInfo_SkeletalMesh, Info_SkeletalMesh, m_stInfo_SkeletalMesh);
};
