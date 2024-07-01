#pragma once
#pragma warning(disable: 4005)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cassert>
#include <memory>
#include <chrono>
#include <vector>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <d3d9.h>
#include <d3dx9.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <DXGI.h>
#include <dinput.h>
#include <dsound.h>
#include <Windows.h>
#include <tchar.h>

#define STR_EMPTY				(std::string(""))
#define VER_EFFECT				(std::string("fx_4_0"))
#define SEMANTIC_POS			(std::string("POSITION"))

#define NAME_COLOR					(std::string("g_stColor"))
#define NAME_COLOR_LIGHT			(std::string("g_stColor_Light"))

#define NAME_NORMAL_MAP_CBUFFER				(std::string("g_oNormalMap"))
#define NAME_DIFFUSE_MAP_CBUFFER			(std::string("g_oDiffuseMap"))

#define NAME_WORLD_MATRIX_CBUFFER				(std::string("g_stMatrix_World"))
#define NAME_VIEW_MATRIX_CBUFFER				(std::string("g_stMatrix_View"))
#define NAME_PROJECTION_MATRIX_CBUFFER			(std::string("g_stMatrix_Projection"))

#define FLAGS_CPU_ACCESS_NONE			((D3D10_CPU_ACCESS_FLAG)0)
#define MAX_NUM_SFXS_DUPLICATE			(10)

#define COLOR_BLACK			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))
#define COLOR_WHITE			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

#define VEC_WORLD_RIGHT				(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
#define VEC_WORLD_UP				(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define VEC_WORLD_FORWARD			(D3DXVECTOR3(0.0f, 0.0f, 1.0f))

#define ELEMENT_END_VERTEX			(D3DVERTEXELEMENT9(D3DDECL_END()))

// 메모리 관리 {
#define SAFE_FREE(TARGET)			if((TARGET) != nullptr) { free((TARGET)); (TARGET) = nullptr; }
#define SAFE_CLOSE(TARGET)			if((TARGET) != nullptr) { fclose((TARGET)); (TARGET) = nullptr; }

#define SAFE_DEL(TARGET)				if((TARGET) != nullptr) { delete (TARGET); (TARGET) = nullptr; }
#define SAFE_DEL_ARRAY(TARGET)			if((TARGET) != nullptr) { delete[] (TARGET); (TARGET) = nullptr; }

#define SAFE_RELEASE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Release(); (TARGET) = nullptr; }
#define SAFE_UNACQUIRE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Unacquire(); SAFE_RELEASE((TARGET)) }
// 메모리 관리 }

// 접근자 {
#define GET_APP_WND()			(CApp_Wnd::GetInst())
#define GET_APP_D3D()			(static_cast<CApp_D3D*>(GET_APP_WND()))

#define GET_MANAGER_RES()			(CManager_Res::GetInst())
#define GET_MANAGER_SND()			(CManager_Snd::GetInst())
#define GET_MANAGER_TIME()			(CManager_Time::GetInst())
#define GET_MANAGER_INPUT()			(CManager_Input::GetInst())

#define GET_HANDLE_WND()			(GET_APP_WND()->GetHandle_Wnd())
#define GET_HANDLE_INST()			(GET_APP_WND()->GetHandle_Inst())

#define GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)			virtual TYPE_DATA Get##NAME_FUNC(void) const { return NAME_VAR; }
#define SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)			virtual void Set##NAME_FUNC(TYPE_DATA a_tVal) { NAME_VAR = a_tVal; }

#define GETTER_PROPERTY(TYPE_DATA, NAME_FUNC, NAME_VAR)			\
private:														\
TYPE_DATA NAME_VAR;												\
public:															\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_PROPERTY_WITH_INIT(TYPE_DATA, NAME_FUNC, NAME_VAR, VAL)			\
private:																		\
TYPE_DATA NAME_VAR = VAL;														\
public:																			\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_SETTER_PROPERTY(TYPE_DATA, NAME_FUNC, NAME_VAR)			\
private:																\
TYPE_DATA NAME_VAR;														\
public:																	\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)									\
SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)

#define GETTER_SETTER_PROPERTY_WITH_INIT(TYPE_DATA, NAME_FUNC, NAME_VAR, VAL)			\
private:																				\
TYPE_DATA NAME_VAR = VAL;																\
public:																					\
GETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)													\
SETTER(TYPE_DATA, NAME_FUNC, NAME_VAR)
// 접근자 }

// 싱글턴
#define SINGLETON(TYPE_CLS)					\
protected:									\
TYPE_CLS(void);								\
virtual ~TYPE_CLS(void);					\
public:										\
static TYPE_CLS* GetInst(void)				\
{											\
	static TYPE_CLS oInst;					\
	return &oInst;							\
}

/** 마우스 버튼 */
enum class EBtnMouse
{
	NONE = -1,
	LEFT,
	RIGHT,
	MIDDLE,
	MAX_VAL
};

/** 본 정보 */
struct STInfo_Bone : public D3DXFRAME
{ 
	D3DXMATRIXA16 m_stMatrix_CombineTrans;
};

/** 메쉬 정보 */
struct STInfo_Mesh
{
	ID3DX10Mesh* m_pXMesh;

	std::vector<D3DMATERIAL9> m_oVectorMaterials;
	std::vector<ID3D10ShaderResourceView*> m_oVectorViews_SR;
};

/** 스켈레톤 메쉬 정보 */
struct STInfo_SkeletonMesh : public STInfo_Mesh
{
	LPD3DXFRAME m_pstXFrame;
	LPD3DXANIMATIONCONTROLLER m_pXController_Anim;
};

/** 메쉬 컨테이너 정보 */
struct STInfo_MeshContainer : public D3DXMESHCONTAINER
{
	// Do Something
};

/** 웨이브 사운드 정보 */
struct STInfo_WaveSnd
{
	int m_nNumBytes;
	WAVEFORMATEX m_stInfo_Wave;

	LPBYTE m_pnBytes;
};
