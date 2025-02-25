#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFunc
{
	template<typename TKey, typename TVal>
	void InsertVal(std::unordered_map<TKey, TVal>& a_rSender,
		const TKey& a_rtKey, const TVal& a_rtVal)
	{
		// 값 추가가 불가능 할 경우
		if(a_rSender.find(a_rtKey) != a_rSender.end())
		{
			return;
		}

		a_rSender.insert(std::make_pair(a_rtKey, a_rtVal));
	}
}
