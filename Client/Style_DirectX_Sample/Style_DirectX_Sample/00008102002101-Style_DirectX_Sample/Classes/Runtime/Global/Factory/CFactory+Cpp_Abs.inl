#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFactory
{
	template<typename TObj, typename ...ARGS>
	TObj* CreateObj(const ARGS&& ...args)
	{
		auto pObj = new TObj(args...);
		pObj->Init();

		return pObj;
	}
}
