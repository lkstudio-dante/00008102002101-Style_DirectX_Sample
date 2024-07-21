#pragma once

#include "../Define/KDefine+Global.h"

namespace Func
{
	/** 데이터 타입 -> 형식으로 변환한다 */
	DXGI_FORMAT DataTypeToFmt(BYTE a_nDataType);

	/** 용도 -> 시멘틱 이름으로 변환한다 */
	LPCSTR UsageToName_Semantic(BYTE a_nUsage);

	/** 정점 요소 -> 입력 요소로 변환한다 */
	D3D10_INPUT_ELEMENT_DESC Element_VertexToDesc_InputElement(D3DVERTEXELEMENT9 a_stElement_Vertex);

	/** 정점 선언 -> 입력 레이아웃으로 변환한다 */
	std::vector<D3D10_INPUT_ELEMENT_DESC> VertexDeclToInputLayout(D3DVERTEXELEMENT9 a_pstElements_Vertex[]);

	/** 메쉬 9 -> 메쉬로 변환한다 */
	ID3DX10Mesh* XMesh9ToXMesh(LPD3DXMESH a_pXMesh9);
}
