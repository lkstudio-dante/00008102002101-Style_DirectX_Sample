#include "CFunc+DirectX_Abs.h"
#include "../Access/CAccess+DirectX_Abs.h"

#include "../Utility/Base/CApp_D3D.h"

namespace CFunc
{
	/** 인덱스 버퍼를 설정한다 */
	static void SetupBuffer_Indices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	/** 정점 버퍼를 설정한다 */
	static void SetupBuffer_Vertices(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	/** 속성 버퍼를 설정한다 */
	static void SetupBuffer_Attributes(ID3DX10Mesh* a_pXMesh, LPD3DXMESH a_pXMesh9);

	LPCSTR UsageToName_Semantic(BYTE a_nUsage)
	{
		switch(a_nUsage)
		{
			case D3DDECLUSAGE_POSITION: return ::G_N_SEMANTIC_POS.c_str();
			case D3DDECLUSAGE_NORMAL: return ::G_N_SEMANTIC_NORMAL.c_str();
			case D3DDECLUSAGE_TEXCOORD: return ::G_N_SEMANTIC_TEXTURE_COORD.c_str();
			case D3DDECLUSAGE_COLOR: return ::G_N_SEMANTIC_COLOR.c_str();
			case D3DDECLUSAGE_TANGENT: return ::G_N_SEMANTIC_TANGENT.c_str();
			case D3DDECLUSAGE_BINORMAL: return ::G_N_SEMANTIC_BINORMAL.c_str();
			case D3DDECLUSAGE_BLENDWEIGHT: return ::G_N_SEMANTIC_BLEND_WEIGHT.c_str();
		}

		return nullptr;
	}

	DXGI_FORMAT DeclTypeToFmt(BYTE a_nDataType)
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

	D3DXMATRIXA16 QuaternionToMatrix_Rotate(const D3DXQUATERNION& a_rstQuaternion)
	{
		D3DXMATRIXA16 stMatrix_Rotate;
		return *D3DXMatrixRotationQuaternion(&stMatrix_Rotate, &a_rstQuaternion);
	}

	D3DXQUATERNION Matrix_RotateToQuaternion(const D3DXMATRIXA16& a_rstMatrix_Rotate)
	{
		D3DXQUATERNION stQuaternion;
		return *D3DXQuaternionRotationMatrix(&stQuaternion, &a_rstMatrix_Rotate);
	}

	D3D10_INPUT_ELEMENT_DESC VertexElementToDesc_InputElement(D3DVERTEXELEMENT9 a_stVertexElement)
	{
		D3D10_INPUT_ELEMENT_DESC stDesc_InputElement;
		ZeroMemory(&stDesc_InputElement, sizeof(stDesc_InputElement));

		stDesc_InputElement.InputSlot = a_stVertexElement.Stream;
		stDesc_InputElement.InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;

		stDesc_InputElement.SemanticName = CFunc::UsageToName_Semantic(a_stVertexElement.Usage);
		stDesc_InputElement.SemanticIndex = a_stVertexElement.UsageIndex;
		stDesc_InputElement.Format = CFunc::DeclTypeToFmt(a_stVertexElement.Type);

		stDesc_InputElement.AlignedByteOffset = a_stVertexElement.Offset;
		stDesc_InputElement.InstanceDataStepRate = 0;

		return stDesc_InputElement;
	}

	std::vector<D3D10_INPUT_ELEMENT_DESC> VertexDeclToInputLayout(const D3DVERTEXELEMENT9 a_pstVertexElements[])
	{
		D3DVERTEXELEMENT9 stVertexElement_End = D3DDECL_END();
		std::vector<D3D10_INPUT_ELEMENT_DESC> oVectorDescs_InputElement;

		int i = 0;

		while(memcmp(a_pstVertexElements + i, &stVertexElement_End, sizeof(stVertexElement_End)) != 0)
		{
			auto stDesc_InputElement = CFunc::VertexElementToDesc_InputElement(*(a_pstVertexElements + i));
			oVectorDescs_InputElement.push_back(stDesc_InputElement);

			i += 1;
		}

		return oVectorDescs_InputElement;
	}

	ID3DX10Mesh* XMesh9ToXMesh(LPD3DXMESH a_pXMesh9)
	{
		D3DVERTEXELEMENT9 astVertexElements[MAX_FVF_DECL_SIZE];
		a_pXMesh9->GetDeclaration(astVertexElements);

		auto oVectorDescs_InputElement = CFunc::VertexDeclToInputLayout(astVertexElements);
		ID3DX10Mesh* pXMesh = nullptr;

		D3DX10CreateMesh(GET_APP_D3D()->GetDevice(),
			&oVectorDescs_InputElement[0], oVectorDescs_InputElement.size(), ::G_N_SEMANTIC_POS.c_str(), a_pXMesh9->GetNumVertices(), a_pXMesh9->GetNumFaces(), D3DX10_MESH_32_BIT, &pXMesh);

		CFunc::SetupBuffer_Indices(pXMesh, a_pXMesh9);
		CFunc::SetupBuffer_Vertices(pXMesh, a_pXMesh9);
		CFunc::SetupBuffer_Attributes(pXMesh, a_pXMesh9);

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

		CopyMemory(pvBuffer, pvBuffer9, a_pXMesh9->GetNumFaces() * sizeof(DWORD));

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

		CopyMemory(pvBuffer,
			pvBuffer9, a_pXMesh9->GetNumVertices() * a_pXMesh9->GetNumBytesPerVertex());

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

		CopyMemory(pvBuffer, pvBuffer9, a_pXMesh9->GetNumFaces() * sizeof(DWORD));

		pXMeshBuffer->Unmap();
		a_pXMesh9->UnlockVertexBuffer();
	}
}
