#pragma once
#pragma warning(disable: 4005)

#define _CRT_SECURE_NO_WARNINGS

#include "KCDefine+C_Abs.h"
#include "KCDefine+Cpp_Abs.h"
#include "KCDefine+WinAPI_Abs.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <DXGI.h>

#include "KCDefine+DirectX_Name.h"
#include "KCDefine+DirectX_Path.h"

#include "KCDefine+DirectX_Vec.h"
#include "KCDefine+DirectX_Decl.h"
#include "KCDefine+DirectX_Color.h"
#include "KCDefine+DirectX_Semantic.h"

#include "KCDefine+DirectX_TypeEnum.h"
#include "KCDefine+DirectX_TypeStruct.h"

// 접근자
#define GET_APP_D3D()					(static_cast<CApp_D3D*>(GET_APP_WIN_API()))
#define GET_MANAGER_D3D_RES()			(CManager_D3DRes::GetInst())

// 기타 {
static const std::string G_VER_EFFECT = "fx_4_0";

static const D3D10_CPU_ACCESS_FLAG G_FLAGS_CPU_ACCESS_NONE = (D3D10_CPU_ACCESS_FLAG)0;
static const D3D10_RESOURCE_MISC_FLAG G_FLAGS_MISC_NONE = (D3D10_RESOURCE_MISC_FLAG)0;
// 기타 }
