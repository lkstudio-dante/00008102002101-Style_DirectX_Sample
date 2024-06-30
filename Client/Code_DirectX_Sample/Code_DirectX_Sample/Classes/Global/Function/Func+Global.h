#pragma once

#include "../Define/KDefine+Global.h"

namespace Func
{
	/** 정점 선언 => 입력 요소로 변환한다 */
	D3D10_INPUT_ELEMENT_DESC Element_VertexToDesc_InputElement(const D3DVERTEXELEMENT9& a_rstElement_Vertex);

	/** 9 메쉬 => 메쉬로 변환한다 */
	ID3DX10Mesh* Mesh9ToMesh(LPD3DXMESH a_pMesh);
}
