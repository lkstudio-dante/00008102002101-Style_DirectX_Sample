#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFunc
{
	template<typename T>
	void FreeResources(std::vector<T>& a_rSender)
	{
		for(auto pRes : a_rSender)
		{
			SAFE_FREE(pRes);
		}

		a_rSender.clear();
	}

	template<typename K, typename V>
	void FreeResources(std::unordered_map<K, V>& a_rSender)
	{
		for(auto& rstKeyVal : a_rSender)
		{
			SAFE_FREE(rstKeyVal.second);
		}

		a_rSender.clear();
	}

	template<typename T>
	void DeleteResources(std::vector<T>& a_rSender)
	{
		for(auto pRes : a_rSender)
		{
			SAFE_DELETE(pRes);
		}

		a_rSender.clear();
	}

	template<typename K, typename V>
	void DeleteResources(std::unordered_map<K, V>& a_rSender)
	{
		for(auto& rstKeyVal : a_rSender)
		{
			SAFE_DELETE(rstKeyVal.second);
		}

		a_rSender.clear();
	}
}
