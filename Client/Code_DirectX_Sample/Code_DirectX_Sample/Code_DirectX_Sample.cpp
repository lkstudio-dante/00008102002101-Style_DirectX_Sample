#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

#include "Classes/Sample/CSample.h"

/** 메인 함수 */
int WINAPI _tWinMain(HINSTANCE a_hInst, HINSTANCE a_hInstPrev, LPTSTR a_pszCmdLine, int a_nOptShow)
{
	SIZE stSizeWnd =
	{
		GetSystemMetrics(SM_CXSCREEN) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2
	};

	return std::shared_ptr<CSample>(new CSample(a_hInst, a_nOptShow, stSizeWnd))->Run();
}
