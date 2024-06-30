#include "CManager_Input.h"
#include "../Base/CApp_D3D.h"

CManager_Input::CManager_Input(void)
{
	ZeroMemory(m_anStates_CurKey, sizeof(m_anStates_CurKey));
	ZeroMemory(m_anStates_PrevKey, sizeof(m_anStates_PrevKey));

	ZeroMemory(&m_stState_CurMouse, sizeof(m_stState_CurMouse));
	ZeroMemory(&m_stState_PrevMouse, sizeof(m_stState_PrevMouse));
}

CManager_Input::~CManager_Input(void)
{
	SAFE_UNACQUIRE(m_pDevice_Mouse);
	SAFE_UNACQUIRE(m_pDevice_Keyboard);

	SAFE_RELEASE(m_pDInput);
}

void CManager_Input::Init(void)
{
	m_pDInput = this->CreateDInput();
	m_pDevice_Mouse = this->CreateDevice_Mouse();
	m_pDevice_Keyboard = this->CreateDevice_Keyboard();
}

void CManager_Input::Update(float a_fTime_Delta)
{
	CopyMemory(m_anStates_PrevKey, m_anStates_CurKey, sizeof(m_anStates_CurKey));
	CopyMemory(&m_stState_PrevMouse, &m_stState_CurMouse, sizeof(m_stState_CurMouse));

	m_pDevice_Mouse->GetDeviceState(sizeof(m_stState_CurMouse), &m_stState_CurMouse);
	m_pDevice_Keyboard->GetDeviceState(sizeof(m_anStates_CurKey), m_anStates_CurKey);
}

bool CManager_Input::IsDown_Key(int a_nCodeKey)
{
	return m_anStates_CurKey[a_nCodeKey] & 0x80;
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

bool CManager_Input::IsDown_MouseBtn(EBtnMouse a_eBtnMouse)
{
	return m_stState_CurMouse.rgbButtons[(int)a_eBtnMouse] & 0x80;
}

bool CManager_Input::IsPress_MouseBtn(EBtnMouse a_eBtnMouse)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eBtnMouse);
	return bIsDown_MouseBtn && !(m_stState_PrevMouse.rgbButtons[(int)a_eBtnMouse] & 0x80);
}

bool CManager_Input::IsRelease_MouseBtn(EBtnMouse a_eBtnMouse)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eBtnMouse);
	return !bIsDown_MouseBtn && (m_stState_PrevMouse.rgbButtons[(int)a_eBtnMouse] & 0x80);
}

int CManager_Input::GetDelta_MouseWheel(void)
{
	return m_stState_CurMouse.lZ;
}

POINT CManager_Input::GetPos_Mouse(void)
{
	POINT stMousePos;
	GetCursorPos(&stMousePos);
	ScreenToClient(GET_HANDLE_WND(), &stMousePos);

	return stMousePos;
}

LPDIRECTINPUT8 CManager_Input::CreateDInput(void)
{
	LPDIRECTINPUT8 pDInput = nullptr;

	DirectInput8Create(GET_HANDLE_INST(),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&pDInput, nullptr);

	return pDInput;
}

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDevice_Mouse(void)
{
	LPDIRECTINPUTDEVICE8 pDevice_Mouse = nullptr;
	m_pDInput->CreateDevice(GUID_SysMouse, &pDevice_Mouse, nullptr);

	pDevice_Mouse->SetDataFormat(&c_dfDIMouse);
	pDevice_Mouse->SetCooperativeLevel(GET_HANDLE_WND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	pDevice_Mouse->Acquire();

	return pDevice_Mouse;
}

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDevice_Keyboard(void)
{
	LPDIRECTINPUTDEVICE8 pDevice_Keyboard = nullptr;
	m_pDInput->CreateDevice(GUID_SysKeyboard, &pDevice_Keyboard, nullptr);

	pDevice_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	pDevice_Keyboard->SetCooperativeLevel(GET_HANDLE_WND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	pDevice_Keyboard->Acquire();

	return pDevice_Keyboard;
}
