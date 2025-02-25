#pragma once

/**
* 정점
*/
struct STVertex
{
	D3DXVECTOR3 m_stPos;
	D3DXVECTOR3 m_stNormal;
	D3DXVECTOR2 m_stUV;
	D3DXVECTOR4 m_stColor;
	D3DXVECTOR3 m_stTangent;
	D3DXVECTOR3 m_stBinormal;
	D3DXVECTOR4 m_stWeight_Blend;
};

/**
* 재질 상수 버퍼
*/
struct STCBuffer_Mat
{
	D3DXCOLOR m_stColor;
	D3DXCOLOR m_stColor_Light;
};

/**
* 행렬 상수 버퍼 
*/
struct STCBuffer_Matrix
{
	D3DXMATRIXA16 m_stMatrix_World;
	D3DXMATRIXA16 m_stMatrix_View;
	D3DXMATRIXA16 m_stMatrix_Projection;
};

/**
* 메쉬 정보
*/
struct STInfo_Mesh
{
	LPDWORD m_pnAdjacency;
	ID3DX10Mesh* m_pXMesh;

	std::vector<D3DMATERIAL9> m_oVectorMaterials;
	std::vector<D3D10_INPUT_ELEMENT_DESC> m_oVectorDescs_InputElement;
	std::vector<ID3D10ShaderResourceView*> m_oVectorViews_SR;
};

/** 
* 본 정보
*/
struct STInfo_Bone : public D3DXFRAME
{
	D3DXMATRIXA16 m_stMatrix_CombineTrans;
};

/** 
* 메쉬 컨테이너 정보
*/
struct STInfo_MeshContainer : public D3DXMESHCONTAINER
{
	ID3DX10Mesh* m_pXMesh;

	std::vector<D3DMATERIAL9> m_oVectorMaterials;
	std::vector<D3DXMATRIXA16> m_oVectorXMatrices_BoneOffset;

	std::vector<D3DXBONECOMBINATION> m_oVectorXCombinations_Bone;
	std::vector<D3D10_INPUT_ELEMENT_DESC> m_oVectorDescs_InputElement;

	std::vector<ID3D10ShaderResourceView*> m_oVectorViews_SR;
};

/**
* 스켈레톤 메쉬 정보
*/
struct STInfo_SkeletalMesh : public STInfo_Mesh
{
	LPD3DXFRAME m_pstXFrame;
	LPD3DXANIMATIONCONTROLLER m_pXController_Anim;
};
