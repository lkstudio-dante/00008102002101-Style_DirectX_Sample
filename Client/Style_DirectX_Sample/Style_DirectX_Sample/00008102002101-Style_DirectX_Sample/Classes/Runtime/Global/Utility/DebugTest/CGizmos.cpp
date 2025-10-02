#include "CGizmos.h"

CGizmos::CGizmos(const std::string& a_rPath_Effect)
	:
	CObj_Debug(a_rPath_Effect)
{
	// Do Something
}

void CGizmos::Render(ID3D10Device* a_pDevice)
{
	CObj_Debug::Render(a_pDevice);
}
