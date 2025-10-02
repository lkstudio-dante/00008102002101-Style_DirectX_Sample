#pragma once

#define G_LIST_VERTEX_ELEMENTS_DEF()																								\
std::initializer_list<D3DVERTEXELEMENT9>																							\
{																																	\
	{ 0, offsetof(STVertex, m_stPos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },						\
	{ 0, offsetof(STVertex, m_stNormal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },						\
	{ 0, offsetof(STVertex, m_stUV), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },							\
	{ 0, offsetof(STVertex, m_stColor), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },							\
	{ 0, offsetof(STVertex, m_stTangent), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },						\
	{ 0, offsetof(STVertex, m_stBinormal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },					\
	{ 0, offsetof(STVertex, m_stWeight_Blend), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },			\
	D3DDECL_END()																													\
}

#define G_LIST_VERTEX_ELEMENTS_DEBUG()																					\
std::initializer_list<D3DVERTEXELEMENT9>																				\
{																														\
	{ 0, offsetof(STVertex, m_stPos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },			\
	D3DDECL_END()																										\
}

#define G_LIST_DESCS_DEF_INPUT_ELEMENT()																														\
std::initializer_list<D3D10_INPUT_ELEMENT_DESC>																													\
{																																								\
	{ ::G_N_SEMANTIC_POS.c_str(), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(STVertex, m_stPos), D3D10_INPUT_PER_VERTEX_DATA, 0 },								\
	{ ::G_N_SEMANTIC_NORMAL.c_str(), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(STVertex, m_stNormal), D3D10_INPUT_PER_VERTEX_DATA, 0 },						\
	{ ::G_N_SEMANTIC_TEXTURE_COORD.c_str(), 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(STVertex, m_stUV), D3D10_INPUT_PER_VERTEX_DATA, 0 },						\
	{ ::G_N_SEMANTIC_COLOR.c_str(), 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(STVertex, m_stColor), D3D10_INPUT_PER_VERTEX_DATA, 0 },						\
	{ ::G_N_SEMANTIC_TANGENT.c_str(), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(STVertex, m_stTangent), D3D10_INPUT_PER_VERTEX_DATA, 0 },						\
	{ ::G_N_SEMANTIC_BINORMAL.c_str(), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(STVertex, m_stBinormal), D3D10_INPUT_PER_VERTEX_DATA, 0 },					\
	{ ::G_N_SEMANTIC_BLEND_WEIGHT.c_str(), 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(STVertex, m_stWeight_Blend), D3D10_INPUT_PER_VERTEX_DATA, 0 }			\
}

#define G_LIST_DESCS_DEBUG_INPUT_ELEMENT()																									\
std::initializer_list<D3D10_INPUT_ELEMENT_DESC>																								\
{																																			\
	{ ::G_N_SEMANTIC_POS.c_str(), 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(STVertex, m_stPos), D3D10_INPUT_PER_VERTEX_DATA, 0 }			\
}
