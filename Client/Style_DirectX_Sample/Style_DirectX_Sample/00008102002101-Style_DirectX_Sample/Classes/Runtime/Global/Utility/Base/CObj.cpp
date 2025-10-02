#include "CObj.h"

CObj::~CObj(void)
{
	this->Release();
	this->Destroy();
}
