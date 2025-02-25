#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"
#include "CAccess+Cpp_Vector.h"

namespace CAccess
{
	template<typename T>
	bool IsValid_Idx(std::vector<T>& a_rSender, int a_nIdx)
	{
		return a_nIdx >= 0 && a_nIdx < a_rSender.size();
	}

	template<typename T>
	T GetVal(std::vector<T>& a_rSender, int a_nIdx, T a_tVal_Def)
	{
		return CAccess::IsValid_Idx(a_rSender, a_nIdx) ? a_rSender[a_nIdx] : a_tVal_Def;
	}
}
