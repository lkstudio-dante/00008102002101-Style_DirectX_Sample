#pragma once

#include "../Define/KCDefine+DirectX_Abs.h"

#include "CFunc+C_Abs.h"
#include "CFunc+Cpp_Abs.h"
#include "CFunc+WinAPI_Abs.h"

namespace CFunc
{
	/** 용도 -> 시멘틱 이름으로 변환한다 */
	LPCSTR UsageToName_Semantic(BYTE a_nUsage);

	/** 데이터 타입 -> 형식으로 변환한다 */
	DXGI_FORMAT DeclTypeToFmt(BYTE a_nDataType);

	/** 사원수 -> 회전 행렬로 변환한다 */
	D3DXMATRIXA16 QuaternionToMatrix_Rotate(const D3DXQUATERNION& a_rstQuaternion);

	/** 회전 행렬 -> 사원수로 변화한다 */
	D3DXQUATERNION Matrix_RotateToQuaternion(const D3DXMATRIXA16& a_rstMatrix_Rotate);

	/** 정점 요소 -> 입력 요소로 변환한다 */
	D3D10_INPUT_ELEMENT_DESC VertexElementToDesc_InputElement(D3DVERTEXELEMENT9 a_stVertexElement);

	/** 정점 선언 -> 입력 레이아웃으로 변환한다 */
	std::vector<D3D10_INPUT_ELEMENT_DESC> VertexDeclToInputLayout(const D3DVERTEXELEMENT9 a_pstVertexElements[]);

	/** 메쉬 9 -> 메쉬로 변환한다 */
	ID3DX10Mesh* XMesh9ToXMesh(LPD3DXMESH a_pXMesh9);
}

#include "CFunc+DirectX_Vec.h"
