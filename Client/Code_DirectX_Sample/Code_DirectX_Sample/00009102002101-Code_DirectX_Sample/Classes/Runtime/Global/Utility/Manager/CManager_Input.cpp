#include "CManager_Input.h"
#include "../../Factory/CFactory+WinAPI_Abs.h"

#include "../Base/CApp_WinAPI.h"

CManager_Input::CManager_Input(void)
{
	ZeroMemory(m_anStates_Key, sizeof(m_anStates_Key));
	ZeroMemory(m_anStates_PrevKey, sizeof(m_anStates_PrevKey));

	ZeroMemory(&m_stState_Mouse, sizeof(m_stState_Mouse));
	ZeroMemory(&m_stState_PrevMouse, sizeof(m_stState_PrevMouse));
}

CManager_Input::~CManager_Input(void)
{
	// Do Something
}

void CManager_Input::Init(void)
{
	m_pDInput = this->CreateDInput();
	m_pDevice_Mouse = this->CreateDevice_Mouse();
	m_pDevice_Keyboard = this->CreateDevice_Keyboard();
}

void CManager_Input::Release(void)
{
	SAFE_UNACQUIRE(m_pDevice_Keyboard);
	SAFE_UNACQUIRE(m_pDevice_Mouse);

	SAFE_RELEASE(m_pDInput);
}

void CManager_Input::Update(void)
{
	CopyMemory(m_anStates_PrevKey, m_anStates_Key, sizeof(m_anStates_Key));
	CopyMemory(&m_stState_PrevMouse, &m_stState_Mouse, sizeof(m_stState_Mouse));

	m_pDevice_Keyboard->GetDeviceState(sizeof(m_anStates_Key), m_anStates_Key);
	m_pDevice_Mouse->GetDeviceState(sizeof(m_stState_Mouse), &m_stState_Mouse);
}

bool CManager_Input::IsDown_Key(int a_nCodeKey)
{
	return m_anStates_Key[a_nCodeKey] & 0x80;
}

bool CManager_Input::IsPress_Key(int a_nCodeKey)
{
	bool bIsDown_Key = this->IsDown_Key(a_nCodeKey);
	return bIsDown_Key && !(m_anStates_PrevKey[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsRelease_Key(int a_nCodeKey)
{
	bool bIsDown_Key = this->IsDown_Key(a_nCodeKey);
	return !bIsDown_Key && (m_anStates_PrevKey[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsDown_MouseBtn(EBtn_Mouse a_eBtn_Mouse)
{
	return m_stState_Mouse.rgbButtons[(int)a_eBtn_Mouse] & 0x80;
}

bool CManager_Input::IsPress_MouseBtn(EBtn_Mouse a_eBtn_Mouse)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eBtn_Mouse);
	return bIsDown_MouseBtn && !(m_stState_PrevMouse.rgbButtons[(int)a_eBtn_Mouse] & 0x80);
}

bool CManager_Input::IsRelease_MouseBtn(EBtn_Mouse a_eBtn_Mouse)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eBtn_Mouse);
	return !bIsDown_MouseBtn && (m_stState_PrevMouse.rgbButtons[(int)a_eBtn_Mouse] & 0x80);
}

int CManager_Input::GetDelta_MouseX(void)
{
	return m_stState_Mouse.lX;
}

int CManager_Input::GetDelta_MouseY(void)
{
	return m_stState_Mouse.lY;
}

int CManager_Input::GetDelta_MouseWheel(void)
{
	return m_stState_Mouse.lZ;
}

POINT CManager_Input::GetPos_Mouse(void)
{
	POINT stPos_Mouse;
	GetCursorPos(&stPos_Mouse);

	ScreenToClient(GET_HANDLE_WND(), &stPos_Mouse);
	return stPos_Mouse;
}

LPDIRECTINPUT8 CManager_Input::CreateDInput(void)
{
	LPDIRECTINPUT8 pDInput = nullptr;

	DirectInput8Create(GET_HANDLE_INST(),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&pDInput, nullptr);

	return pDInput;
}

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDevice_Keyboard(void)
{
	return CFactory::CreateDevice_Input(GUID_SysKeyboard,
		&c_dfDIKeyboard, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDevice_Mouse(void)
{
	return CFactory::CreateDevice_Input(GUID_SysMouse, 
		&c_dfDIMouse, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}
