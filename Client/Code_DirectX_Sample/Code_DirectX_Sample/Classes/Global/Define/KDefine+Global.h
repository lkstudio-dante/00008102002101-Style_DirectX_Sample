#pragma once
#pragma warning(disable: 4005)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cassert>
#include <memory>
#include <chrono>
#include <vector>
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

#define VER_EFFECT						(std::string("fx_4_0"))
#define FLAGS_CPU_ACCESS_NONE			((D3D10_CPU_ACCESS_FLAG)0)

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

#define GET_HANDLE_WND()			(GET_APP_WND()->GetHandleWnd())
#define GET_HANDLE_INST()			(GET_APP_WND()->GetHandleInst())

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
