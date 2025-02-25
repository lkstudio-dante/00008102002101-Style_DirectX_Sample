#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "KCDefine+C_Abs.h"
#include "KCDefine+Cpp_Abs.h"

#include <dinput.h>
#include <dsound.h>
#include <glm.hpp>

#include <Windows.h>
#include <tchar.h>

// 메모리
#define SAFE_RELEASE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Release(); (TARGET) = nullptr; }
#define SAFE_UNACQUIRE(TARGET)			if((TARGET) != nullptr) { (TARGET)->Unacquire(); SAFE_RELEASE((TARGET)) }

// 접근자 {
#define GET_APP_WIN_API()			(CApp_WinAPI::GetInst())

#define GET_HANDLE_WND()			(GET_APP_WIN_API()->GetHandle_Wnd())
#define GET_HANDLE_INST()			(GET_APP_WIN_API()->GetHandle_Inst())

#define GET_MANAGER_SND()					(CManager_Snd::GetInst())
#define GET_MANAGER_INPUT()					(CManager_Input::GetInst())
#define GET_MANAGER_WIN_API_RES()			(CManager_WinAPIRes::GetInst())
// 접근자 }

// 기타
static const int G_NUM_SFXS_MAX_DUPLICATE = 10;

#include "KCDefine+WinAPI_TypeEnum.h"
#include "KCDefine+WinAPI_TypeStruct.h"
