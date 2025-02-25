#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFunc
{
	/** 값을 추가한다 */
	template<typename TKey, typename TVal>
	void InsertVal(std::unordered_map<TKey, TVal>& a_rSender,
		const TKey& a_rtKey, const TVal& a_rtVal);
}

#include "CFunc+Cpp_Map.inl"
