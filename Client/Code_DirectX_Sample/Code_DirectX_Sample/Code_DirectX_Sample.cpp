#include "00009102002101-Code_DirectX_Sample/Classes/Runtime/Global/Utility/Base/CApp_D3D.h"

/**
* 어플리케이션
*/
class CApp : public CApp_D3D
{
public:			// public 함수

	/** 생성자 */
	CApp(HINSTANCE a_hInst, int a_nOpt_Show, const SIZE& a_rstSize_Wnd)
		:
		CApp_D3D(a_hInst, a_nOpt_Show, a_rstSize_Wnd)
	{
		// Do Something
	}
};

/** 메인 함수 */
int WINAPI _tWinMain(HINSTANCE a_hInst,
	HINSTANCE a_hInst_Prev, LPTSTR a_pszCmdLine, int a_nOpt_Show)
{
	SIZE stSize_Wnd =
	{
		GetSystemMetrics(SM_CXSCREEN) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2
	};

	return std::make_shared<CApp>(a_hInst, a_nOpt_Show, stSize_Wnd)->Run();
}
