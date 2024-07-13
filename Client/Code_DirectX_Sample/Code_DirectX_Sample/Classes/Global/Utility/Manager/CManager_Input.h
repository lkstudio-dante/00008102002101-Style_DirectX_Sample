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
	virtual void Update(float a_fTime_Delta) override;

public:   // public 함수

	/** Direct Input 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUT8, DInput, m_pDInput, nullptr);

	/** 마우스 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, Device_Mouse, m_pDevice9_Mouse, nullptr);

	/** 키보드 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, Device_Keyboard, m_pDevice9_Keyboard, nullptr);

public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Input);

	/** 초기화 */
	virtual void Init(void);

	/** 키 눌림 여부를 반환한다 */
	bool IsDown_Key(int a_nCodeKey);

	/** 키 눌림 시작 여부를 반환한다 */
	bool IsPress_Key(int a_nCodeKey);

	/** 키 눌림 종료 여부를 반환한다 */
	bool IsRelease_Key(int a_nCodeKey);

	/** 마우스 버튼 눌림 여부를 반환한다 */
	bool IsDown_MouseBtn(EMouseBtn a_eMouseBtn);

	/** 마우스 버튼 눌림 시작 여부를 반환한다 */
	bool IsPress_MouseBtn(EMouseBtn a_eMouseBtn);

	/** 마우스 버튼 눌림 종료 여부를 반환한다 */
	bool IsRelease_MouseBtn(EMouseBtn a_eMouseBtn);

public:			// public 접근 함수

	/** 마우스 X 간격을 반환한다 */
	int GetDelta_MouseX(void);

	/** 마우스 Y 간격을 반환한다 */
	int GetDelta_MouseY(void);

	/** 마우스 휠 간격을 반환한다 */
	int GetDelta_MouseWheel(void);

	/** 마우스 위치를 반환한다 */
	POINT GetPos_Mouse(void);

private:			// private 팩토리 함수

	/** Direct Input 을 생성한다 */
	LPDIRECTINPUT8 CreateDInput(void);

	/** 마우스 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDevice_Mouse(void);

	/** 키보드 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDevice_Keyboard(void);

private:			// private 변수

	UCHAR m_anCurStates_Key[UCHAR_MAX + 1];
	UCHAR m_anPrevStates_Key[UCHAR_MAX + 1];

	DIMOUSESTATE m_stCurState_Mouse;
	DIMOUSESTATE m_stPrevState_Mouse;
};
