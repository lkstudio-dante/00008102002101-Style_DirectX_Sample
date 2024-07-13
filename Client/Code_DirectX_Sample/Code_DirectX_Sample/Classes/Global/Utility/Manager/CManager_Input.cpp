#include "CManager_Input.h"
#include "../Base/CApp_D3D.h"

CManager_Input::CManager_Input(void)
{
	ZeroMemory(m_anCurStates_Key, sizeof(m_anCurStates_Key));
	ZeroMemory(m_anPrevStates_Key, sizeof(m_anPrevStates_Key));

	ZeroMemory(&m_stCurState_Mouse, sizeof(m_stCurState_Mouse));
	ZeroMemory(&m_stPrevState_Mouse, sizeof(m_stPrevState_Mouse));
}

CManager_Input::~CManager_Input(void)
{
	SAFE_UNACQUIRE(m_pDevice9_Mouse);
	SAFE_UNACQUIRE(m_pDevice9_Keyboard);

	SAFE_RELEASE(m_pDInput);
}

void CManager_Input::Init(void)
{
	m_pDInput = this->CreateDInput();
	m_pDevice9_Mouse = this->CreateDevice_Mouse();
	m_pDevice9_Keyboard = this->CreateDevice_Keyboard();
}

void CManager_Input::Update(float a_fTime_Delta)
{
	CopyMemory(m_anPrevStates_Key, m_anCurStates_Key, sizeof(m_anCurStates_Key));
	CopyMemory(&m_stPrevState_Mouse, &m_stCurState_Mouse, sizeof(m_stCurState_Mouse));

	m_pDevice9_Mouse->GetDeviceState(sizeof(m_stCurState_Mouse), &m_stCurState_Mouse);
	m_pDevice9_Keyboard->GetDeviceState(sizeof(m_anCurStates_Key), m_anCurStates_Key);
}

bool CManager_Input::IsDown_Key(int a_nCodeKey)
{
	return m_anCurStates_Key[a_nCodeKey] & 0x80;
}

bool CManager_Input::IsPress_Key(int a_nCodeKey)
{
	bool bIsDown_Key = this->IsDown_Key(a_nCodeKey);
	return bIsDown_Key && !(m_anPrevStates_Key[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsRelease_Key(int a_nCodeKey)
{
	bool bIsDown_Key = this->IsDown_Key(a_nCodeKey);
	return !bIsDown_Key && (m_anPrevStates_Key[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsDown_MouseBtn(EMouseBtn a_eMouseBtn)
{
	return m_stCurState_Mouse.rgbButtons[(int)a_eMouseBtn] & 0x80;
}

bool CManager_Input::IsPress_MouseBtn(EMouseBtn a_eMouseBtn)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eMouseBtn);
	return bIsDown_MouseBtn && !(m_stPrevState_Mouse.rgbButtons[(int)a_eMouseBtn] & 0x80);
}

bool CManager_Input::IsRelease_MouseBtn(EMouseBtn a_eMouseBtn)
{
	bool bIsDown_MouseBtn = this->IsDown_MouseBtn(a_eMouseBtn);
	return !bIsDown_MouseBtn && (m_stPrevState_Mouse.rgbButtons[(int)a_eMouseBtn] & 0x80);
}

int CManager_Input::GetDelta_MouseX(void)
{
	return m_stCurState_Mouse.lX;
}

int CManager_Input::GetDelta_MouseY(void)
{
	return m_stCurState_Mouse.lY;
}

int CManager_Input::GetDelta_MouseWheel(void)
{
	return m_stCurState_Mouse.lZ;
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
