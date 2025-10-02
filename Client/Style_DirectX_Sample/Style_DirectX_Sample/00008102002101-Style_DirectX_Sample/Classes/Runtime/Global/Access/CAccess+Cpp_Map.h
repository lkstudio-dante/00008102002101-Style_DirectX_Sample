#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CAccess
{
	/** 값을 반환한다 */
	template<typename TKey, typename TVal>
	TKey GetVal(std::unordered_map<TKey, TVal>& a_rSender, TKey a_tKey, TVal a_tVal_Def);
}

#include "CAccess+Cpp_Map.inl"
