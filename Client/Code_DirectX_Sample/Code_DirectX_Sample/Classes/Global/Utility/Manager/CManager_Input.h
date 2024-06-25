#pragma once

#include "../../Define/KDefine+Global.h"
#include "../Interface/IUpdateable.h"

/**
 * 입력 관리자
 */
class CManager_Input : public virtual IUpdateable
{
public:			// IUpdateable

	/** 상태를 갱신한다 */
	virtual void OnUpdate(const float a_fTimeDelta) override;

public:   // public 함수

	/** Direct Input 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUT8, DInput, m_pDInput, nullptr);

	/** 마우스 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, DeviceMouse, m_pDeviceMouse, nullptr);

	/** 키보드 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, DeviceKeyboard, m_pDeviceKeyboard, nullptr);

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Input);

	/** 초기화 */
	virtual void Init(void);

	/** 키 눌림 여부를 반환한다 */
	bool IsDownKey(int a_nCodeKey);

	/** 키 눌림 시작 여부를 반환한다 */
	bool IsPressKey(int a_nCodeKey);

	/** 키 눌림 종료 여부를 반환한다 */
	bool IsReleaseKey(int a_nCodeKey);

	/** 마우스 버튼 눌림 여부를 반환한다 */
	bool IsDownBtnMouse(EBtnMouse a_eBtnMouse);

	/** 마우스 버튼 눌림 시작 여부를 반환한다 */
	bool IsPressBtnMouse(EBtnMouse a_eBtnMouse);

	/** 마우스 버튼 눌림 종료 여부를 반환한다 */
	bool IsReleaseBtnMouse(EBtnMouse a_eBtnMouse);

public:			// public 접근 함수

	/** 마우스 휠 간격을 반환한다 */
	int GetDeltaMouseWheel(void);

	/** 마우스 위치를 반환한다 */
	POINT GetPosMouse(void);

private:			// private 팩토리 함수

	/** Direct Input 을 생성한다 */
	LPDIRECTINPUT8 CreateDInput(void);

	/** 마우스 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDeviceMouse(void);

	/** 키보드 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDeviceKeyboard(void);

private:			// private 변수

	UCHAR m_anStatesCurKey[UCHAR_MAX + 1];
	UCHAR m_anStatesPrevKey[UCHAR_MAX + 1];

	DIMOUSESTATE m_stStateCurMouse;
	DIMOUSESTATE m_stStatePrevMouse;
};
