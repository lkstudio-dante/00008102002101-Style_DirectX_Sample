#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFactory
{
	/** 객체를 생성한다 */
	template<typename TObj, typename ...ARGS>
	TObj* CreateObj(const ARGS&& ...args);
}

#include "CFactory+Cpp_Abs.inl"
