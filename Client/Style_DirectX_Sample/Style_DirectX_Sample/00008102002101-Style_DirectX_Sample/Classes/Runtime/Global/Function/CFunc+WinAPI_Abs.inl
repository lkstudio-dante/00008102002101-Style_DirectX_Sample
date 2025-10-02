#pragma once

#include "../Define/KCDefine+WinAPI_Abs.h"

namespace CFunc
{
	template<typename T>
	void ReleaseResources(std::vector<T>& a_rSender)
	{
		for(auto pRes : a_rSender)
		{
			SAFE_RELEASE(pRes);
		}

		a_rSender.clear();
	}

	template<typename K, typename V>
	void ReleaseResources(std::unordered_map<K, V>& a_rSender)
	{
		for(auto& rstKeyVal : a_rSender)
		{
			SAFE_RELEASE(rstKeyVal.second);
		}

		a_rSender.clear();
	}

	template<typename T>
	void UnacquireResources(std::vector<T>& a_rSender)
	{
		for(auto pRes : a_rSender)
		{
			SAFE_UNACQUIRE(pRes);
		}

		a_rSender.clear();
	}

	template<typename K, typename V>
	void UnacquireResources(std::unordered_map<K, V>& a_rSender)
	{
		for(auto& rstKeyVal : a_rSender)
		{
			SAFE_UNACQUIRE(rstKeyVal.second);
		}

		a_rSender.clear();
	}
}
