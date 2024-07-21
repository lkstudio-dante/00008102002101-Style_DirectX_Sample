#include "Func+Global.h"
#include "../Access/Access+Global.h"
#include "../Utility/Base/CApp_D3D.h"

namespace Func
{
	/** 인덱스 버퍼를 설정한다 */
	static void SetupBuffer_Indices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	/** 정점 버퍼를 설정한다 */
	static void SetupBuffer_Vertices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	/** 속성 버퍼를 설정한다 */
	static void SetupBuffer_Attributes(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	DXGI_FORMAT DataTypeToFmt(BYTE a_nDataType)
	{
		switch(a_nDataType)
		{
			case D3DDECLTYPE_FLOAT1: return DXGI_FORMAT_R32_FLOAT;
			case D3DDECLTYPE_FLOAT2: return DXGI_FORMAT_R32G32_FLOAT;
			case D3DDECLTYPE_FLOAT3: return DXGI_FORMAT_R32G32B32_FLOAT;
			case D3DDECLTYPE_FLOAT4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	LPCSTR UsageToName_Semantic(BYTE a_nUsage)
	{
		switch(a_nUsage)
		{
			case D3DDECLUSAGE_POSITION: return "POSITION";
			case D3DDECLUSAGE_COLOR: return "COLOR";
			case D3DDECLUSAGE_NORMAL: return "NORMAL";
			case D3DDECLUSAGE_TANGENT: return "TANGENT";
			case D3DDECLUSAGE_BINORMAL: return "BINORMAL";
			case D3DDECLUSAGE_TEXCOORD: return "TEXCOORD";
			case D3DDECLUSAGE_BLENDWEIGHT: return "BLENDWEIGHT";
		}

		return nullptr;
	}

	D3D10_INPUT_ELEMENT_DESC Element_VertexToDesc_InputElement(D3DVERTEXELEMENT9 a_stElement_Vertex)
	{
		D3D10_INPUT_ELEMENT_DESC stDesc_InputElement;
		ZeroMemory(&stDesc_InputElement, sizeof(stDesc_InputElement));

		stDesc_InputElement.InputSlot = a_stElement_Vertex.Stream;
		stDesc_InputElement.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;

		stDesc_InputElement.SemanticName = Func::UsageToName_Semantic(a_stElement_Vertex.Usage);
		stDesc_InputElement.SemanticIndex = a_stElement_Vertex.UsageIndex;
		stDesc_InputElement.Format = Func::DataTypeToFmt(a_stElement_Vertex.Type);

		stDesc_InputElement.AlignedByteOffset = a_stElement_Vertex.Offset;
		stDesc_InputElement.InstanceDataStepRate = 0;

		return stDesc_InputElement;
	}

	std::vector<D3D10_INPUT_ELEMENT_DESC> VertexDeclToInputLayout(D3DVERTEXELEMENT9 a_pstElements_Vertex[])
	{
		auto pstElement_Vertex = a_pstElements_Vertex;
		D3DVERTEXELEMENT9 stElement_EndVertex = D3DDECL_END();

		std::vector<D3D10_INPUT_ELEMENT_DESC> oVectorDescs_InputElement;

		while(true)
		{
			// 변환이 불가능 할 경우
			if(memcmp(pstElement_Vertex, &stElement_EndVertex, sizeof(stElement_EndVertex)) == 0)
			{
				break;
			}

			auto stDesc_InputElement = Func::Element_VertexToDesc_InputElement(*pstElement_Vertex);
			oVectorDescs_InputElement.push_back(stDesc_InputElement);

			pstElement_Vertex += 1;
		}

		return oVectorDescs_InputElement;
	}

	ID3DX10Mesh* XMesh9ToXMesh(LPD3DXMESH a_pXMesh9)
	{
		D3DVERTEXELEMENT9 astElements_Vertex[MAX_FVF_DECL_SIZE];
		a_pXMesh9->GetDeclaration(astElements_Vertex);

		auto oVectorDescs_InputElement = Func::VertexDeclToInputLayout(astElements_Vertex);
		ID3DX10Mesh* pXMesh = nullptr;

		D3DX10CreateMesh(GET_APP_D3D()->GetDevice(),
			&oVectorDescs_InputElement[0], oVectorDescs_InputElement.size(), SEMANTIC_POS.c_str(), a_pXMesh9->GetNumVertices(), a_pXMesh9->GetNumFaces(), D3DX10_MESH_32_BIT, &pXMesh);

		Func::SetupBuffer_Indices(pXMesh, a_pXMesh9);
		Func::SetupBuffer_Vertices(pXMesh, a_pXMesh9);
		Func::SetupBuffer_Attributes(pXMesh, a_pXMesh9);

		return pXMesh;
	}

	void SetupBuffer_Indices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9)
	{
		ID3DX10MeshBuffer* pXMeshBuffer = nullptr;
		a_pXMesh->GetIndexBuffer(&pXMeshBuffer);

		LPVOID pvBuffer = nullptr;
		LPVOID pvBuffer9 = nullptr;

		bool bIsValid = SUCCEEDED(pXMeshBuffer->Map(&pvBuffer, nullptr));
		bIsValid = bIsValid && SUCCEEDED(a_pXMesh9->LockIndexBuffer(0, &pvBuffer9));

		// 버퍼 설정이 불가능 할 경우
		if(!bIsValid)
		{
			return;
		}

		memcpy(pvBuffer, pvBuffer9, a_pXMesh9->GetNumFaces() * sizeof(DWORD));

		pXMeshBuffer->Unmap();
		a_pXMesh9->UnlockIndexBuffer();
	}

	void SetupBuffer_Vertices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9)
	{
		ID3DX10MeshBuffer* pXMeshBuffer = nullptr;
		a_pXMesh->GetVertexBuffer(0, &pXMeshBuffer);

		LPVOID pvBuffer = nullptr;
		LPVOID pvBuffer9 = nullptr;

		bool bIsValid = SUCCEEDED(pXMeshBuffer->Map(&pvBuffer, nullptr));
		bIsValid = bIsValid && SUCCEEDED(a_pXMesh9->LockVertexBuffer(0, &pvBuffer9));

		// 버퍼 설정이 불가능 할 경우
		if(!bIsValid)
		{
			return;
		}

		memcpy(pvBuffer, pvBuffer9, a_pXMesh9->GetNumVertices() * a_pXMesh9->GetNumBytesPerVertex());

		pXMeshBuffer->Unmap();
		a_pXMesh9->UnlockVertexBuffer();
	}

	void SetupBuffer_Attributes(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9)
	{
		ID3DX10MeshBuffer* pXMeshBuffer = nullptr;
		a_pXMesh->GetAttributeBuffer(&pXMeshBuffer);

		LPVOID pvBuffer = nullptr;
		LPVOID pvBuffer9 = nullptr;

		bool bIsValid = SUCCEEDED(pXMeshBuffer->Map(&pvBuffer, nullptr));
		bIsValid = bIsValid && SUCCEEDED(a_pXMesh9->LockAttributeBuffer(0, (LPDWORD*)&pvBuffer9));

		// 버퍼 설정이 불가능 할 경우
		if(!bIsValid)
		{
			return;
		}

		memcpy(pvBuffer, pvBuffer9, a_pXMesh9->GetNumFaces() * sizeof(DWORD));

		pXMeshBuffer->Unmap();
		a_pXMesh9->UnlockVertexBuffer();
	}
}
