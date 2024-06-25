#include "CManager_Input.h"
#include "../Base/CApp_D3D.h"

CManager_Input::CManager_Input(void)
{
	ZeroMemory(m_anStatesCurKey, sizeof(m_anStatesCurKey));
	ZeroMemory(m_anStatesPrevKey, sizeof(m_anStatesPrevKey));

	ZeroMemory(&m_stStateCurMouse, sizeof(m_stStateCurMouse));
	ZeroMemory(&m_stStatePrevMouse, sizeof(m_stStatePrevMouse));
}

CManager_Input::~CManager_Input(void)
{
	SAFE_UNACQUIRE(m_pDeviceMouse);
	SAFE_UNACQUIRE(m_pDeviceKeyboard);

	SAFE_RELEASE(m_pDInput);
}

void CManager_Input::Init(void)
{
	m_pDInput = this->CreateDInput();
	m_pDeviceMouse = this->CreateDeviceMouse();
	m_pDeviceKeyboard = this->CreateDeviceKeyboard();
}

void CManager_Input::OnUpdate(const float a_fTimeDelta)
{
	CopyMemory(m_anStatesPrevKey, m_anStatesCurKey, sizeof(m_anStatesCurKey));
	CopyMemory(&m_stStatePrevMouse, &m_stStateCurMouse, sizeof(m_stStateCurMouse));

	m_pDeviceMouse->GetDeviceState(sizeof(m_stStateCurMouse), &m_stStateCurMouse);
	m_pDeviceKeyboard->GetDeviceState(sizeof(m_anStatesCurKey), m_anStatesCurKey);
}

bool CManager_Input::IsDownKey(int a_nCodeKey)
{
	return m_anStatesCurKey[a_nCodeKey] & 0x80;
}

bool CManager_Input::IsPressKey(int a_nCodeKey)
{
	bool bIsDownKey = this->IsDownKey(a_nCodeKey);
	return bIsDownKey && !(m_anStatesPrevKey[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsReleaseKey(int a_nCodeKey)
{
	bool bIsDownKey = this->IsDownKey(a_nCodeKey);
	return !bIsDownKey && (m_anStatesPrevKey[a_nCodeKey] & 0x80);
}

bool CManager_Input::IsDownBtnMouse(EBtnMouse a_eBtnMouse)
{
	return m_stStateCurMouse.rgbButtons[(int)a_eBtnMouse] & 0x80;
}

bool CManager_Input::IsPressBtnMouse(EBtnMouse a_eBtnMouse)
{
	bool bIsDownBtnMouse = this->IsDownBtnMouse(a_eBtnMouse);
	return bIsDownBtnMouse && !(m_stStatePrevMouse.rgbButtons[(int)a_eBtnMouse] & 0x80);
}

bool CManager_Input::IsReleaseBtnMouse(EBtnMouse a_eBtnMouse)
{
	bool bIsDownBtnMouse = this->IsDownBtnMouse(a_eBtnMouse);
	return !bIsDownBtnMouse && (m_stStatePrevMouse.rgbButtons[(int)a_eBtnMouse] & 0x80);
}

int CManager_Input::GetDeltaMouseWheel(void)
{
	return m_stStateCurMouse.lZ;
}

POINT CManager_Input::GetPosMouse(void)
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

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDeviceMouse(void)
{
	LPDIRECTINPUTDEVICE8 pDeviceMouse = nullptr;
	m_pDInput->CreateDevice(GUID_SysMouse, &pDeviceMouse, nullptr);

	pDeviceMouse->SetDataFormat(&c_dfDIMouse);
	pDeviceMouse->SetCooperativeLevel(GET_HANDLE_WND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	pDeviceMouse->Acquire();

	return pDeviceMouse;
}

LPDIRECTINPUTDEVICE8 CManager_Input::CreateDeviceKeyboard(void)
{
	LPDIRECTINPUTDEVICE8 pDeviceKeyboard = nullptr;
	m_pDInput->CreateDevice(GUID_SysKeyboard, &pDeviceKeyboard, nullptr);

	pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
	pDeviceKeyboard->SetCooperativeLevel(GET_HANDLE_WND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	pDeviceKeyboard->Acquire();

	return pDeviceKeyboard;
}
