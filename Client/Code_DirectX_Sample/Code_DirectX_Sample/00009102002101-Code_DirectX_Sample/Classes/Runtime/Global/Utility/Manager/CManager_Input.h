#pragma once

#include "../../Define/KCDefine+WinAPI_Abs.h"
#include "../Base/CObj.h"

/**
* 입력 관리자
*/
class CManager_Input : public CObj
{
public:			// public 함수

	/** 싱글턴 */
	SINGLETON(CManager_Input);

	/** 초기화 */
	virtual void Init(void) override;

	/** 리소스를 해제한다 */
	virtual void Release(void) override;

	/** 상태를 갱신한다 */
	virtual void Update(void) override;

	/** 키 눌림 여부를 반환한다 */
	bool IsDown_Key(int a_nCodeKey);

	/** 키 눌림 시작 여부를 반환한다 */
	bool IsPress_Key(int a_nCodeKey);

	/** 키 눌림 종료 여부를 반환한다 */
	bool IsRelease_Key(int a_nCodeKey);

	/** 마우스 버튼 눌림 여부를 반환한다 */
	bool IsDown_MouseBtn(EBtn_Mouse a_eBtn_Mouse);

	/** 마우스 버튼 눌림 시작 여부를 반환한다 */
	bool IsPress_MouseBtn(EBtn_Mouse a_eBtn_Mouse);

	/** 마우스 버튼 눌림 종료 여부를 반환한다 */
	bool IsRelease_MouseBtn(EBtn_Mouse a_eBtn_Mouse);

	/** Direct Input 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUT8, DInput, m_pDInput, nullptr);

	/** 키보드 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, Device_Keyboard, m_pDevice_Keyboard, nullptr);

	/** 마우스 디바이스 프로퍼티 */
	GETTER_PROPERTY_WITH_INIT(LPDIRECTINPUTDEVICE8, Device_Mouse, m_pDevice_Mouse, nullptr);

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

	/** 키보드 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDevice_Keyboard(void);

	/** 마우스 디바이스를 생성한다 */
	LPDIRECTINPUTDEVICE8 CreateDevice_Mouse(void);

private:			// private 변수

	UCHAR m_anStates_Key[UCHAR_MAX + 1];
	UCHAR m_anStates_PrevKey[UCHAR_MAX + 1];

	DIMOUSESTATE m_stState_Mouse;
	DIMOUSESTATE m_stState_PrevMouse;
};
