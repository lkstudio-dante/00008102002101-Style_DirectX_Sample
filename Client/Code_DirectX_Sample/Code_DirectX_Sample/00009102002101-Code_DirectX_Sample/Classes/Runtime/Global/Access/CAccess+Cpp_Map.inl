#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CAccess
{
	template<typename TKey, typename TVal>
	TKey GetVal(std::unordered_map<TKey, TVal>& a_rSender, TKey a_tKey, TVal a_tVal_Def)
	{
		auto oIterator = a_rSender.find(a_tKey);
		return (oIterator == a_rSender.end()) ? oIterator->second : a_tVal_Def;
	}
}
