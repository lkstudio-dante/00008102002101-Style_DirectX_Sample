#include "Func+Global.h"
#include "../Access/Access+Global.h"
#include "../Utility/Base/CApp_D3D.h"

namespace Func
{
	/** 인덱스를 설정한다 */
	static void SetupIndices(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh);

	/** 정점을 설정한다 */
	static void SetupVertices(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh);

	/** 속성을 설정한다 */
	static void SetupAttributes(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh);

	D3D10_INPUT_ELEMENT_DESC Element_VertexToDesc_InputElement(const D3DVERTEXELEMENT9& a_rstElement_Vertex)
	{
		D3D10_INPUT_ELEMENT_DESC stDesc_InputElement;
		ZeroMemory(&stDesc_InputElement, sizeof(stDesc_InputElement));

		stDesc_InputElement.InputSlot = a_rstElement_Vertex.Stream;
		stDesc_InputElement.SemanticName = Access::GetName_Semantic(a_rstElement_Vertex.Usage);
		stDesc_InputElement.SemanticIndex = a_rstElement_Vertex.UsageIndex;
		stDesc_InputElement.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
		stDesc_InputElement.AlignedByteOffset = a_rstElement_Vertex.Offset;
		stDesc_InputElement.Format = Access::GetFmt_InputElement(a_rstElement_Vertex.Type);

		return stDesc_InputElement;
	}

	ID3DX10Mesh* XMesh9ToXMesh(LPD3DXMESH a_pXMesh9)
	{
		D3DVERTEXELEMENT9 astElements_Vertex[MAX_FVF_DECL_SIZE];
		a_pXMesh9->GetDeclaration(astElements_Vertex);

		std::vector<D3D10_INPUT_ELEMENT_DESC> oVectorDescs_InputElement;

		for(int i = 0; i < MAX_FVF_DECL_SIZE && astElements_Vertex[i].Stream != ELEMENT_END_VERTEX.Stream; ++i)
		{
			auto stDesc_InputElement = Func::Element_VertexToDesc_InputElement(astElements_Vertex[i]);
			oVectorDescs_InputElement.push_back(stDesc_InputElement);
		}

		ID3DX10Mesh* pXMesh = nullptr;

		D3DX10CreateMesh(GET_APP_D3D()->GetDevice(),
			&oVectorDescs_InputElement[0], oVectorDescs_InputElement.size(), SEMANTIC_POS.c_str(), a_pXMesh9->GetNumVertices(), a_pXMesh9->GetNumFaces(), D3DX10_MESH_32_BIT, &pXMesh);

		Func::SetupIndices(a_pXMesh9, pXMesh);
		Func::SetupVertices(a_pXMesh9, pXMesh);
		Func::SetupAttributes(a_pXMesh9, pXMesh);

		return pXMesh;
	}

	void SetupIndices(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh)
	{
		ID3DX10MeshBuffer* pXBuffer_Idx = nullptr;
		a_pOutXMesh->GetIndexBuffer(&pXBuffer_Idx);

		LPVOID pvIndices = nullptr;
		LPVOID pvIndices9 = nullptr;

		// 인덱스 설정이 불가능 할 경우
		if(FAILED(pXBuffer_Idx->Map(&pvIndices, nullptr)) || FAILED(a_pXMesh9->LockIndexBuffer(0, &pvIndices9)))
		{
			return;
		}

		memcpy(pvIndices, pvIndices9, sizeof(DWORD) * a_pXMesh9->GetNumFaces() * 3);
		pXBuffer_Idx->Unmap();

		a_pXMesh9->UnlockIndexBuffer();
	}

	void SetupVertices(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh)
	{
		ID3DX10MeshBuffer* pXBuffer_Vertex = nullptr;
		a_pOutXMesh->GetVertexBuffer(0, &pXBuffer_Vertex);

		LPVOID pvVertices = nullptr;
		LPVOID pvVertices9 = nullptr;

		// 정점 설정이 불가능 할 경우
		if(FAILED(pXBuffer_Vertex->Map(&pvVertices, nullptr)) || FAILED(a_pXMesh9->LockVertexBuffer(0, &pvVertices9)))
		{
			return;
		}

		memcpy(pvVertices, pvVertices9, a_pXMesh9->GetNumBytesPerVertex() * a_pXMesh9->GetNumVertices());
		pXBuffer_Vertex->Unmap();

		a_pXMesh9->UnlockVertexBuffer();
	}

	void SetupAttributes(ID3DXMesh* a_pXMesh9, ID3DX10Mesh* a_pOutXMesh)
	{
		ID3DX10MeshBuffer* pXBuffer_Attribute = nullptr;
		a_pOutXMesh->GetAttributeBuffer(&pXBuffer_Attribute);

		LPVOID pvAttributes = nullptr;
		LPDWORD pnAttributes9 = nullptr;

		// 속성 설정이 불가능 할 경우
		if(FAILED(pXBuffer_Attribute->Map(&pvAttributes, nullptr)) || FAILED(a_pXMesh9->LockAttributeBuffer(0, &pnAttributes9)))
		{
			return;
		}

		DWORD nSize_Attributes = 0;
		a_pXMesh9->GetAttributeTable(nullptr, &nSize_Attributes);

		memcpy(pvAttributes, pnAttributes9, sizeof(D3DXATTRIBUTERANGE) * nSize_Attributes);
		pXBuffer_Attribute->Unmap();

		a_pXMesh9->UnlockAttributeBuffer();
	}
}
