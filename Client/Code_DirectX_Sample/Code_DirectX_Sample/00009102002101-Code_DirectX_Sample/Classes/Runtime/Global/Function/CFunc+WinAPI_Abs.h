#pragma once

#include "../Define/KCDefine+WinAPI_Abs.h"

#include "CFunc+C_Abs.h"
#include "CFunc+Cpp_Abs.h"

namespace CFunc
{
	/** 리소스를 제거한다 */
	template<typename T>
	void ReleaseResources(std::vector<T>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename K, typename V>
	void ReleaseResources(std::unordered_map<K, V>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename T>
	void UnacquireResources(std::vector<T>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename K, typename V>
	void UnacquireResources(std::unordered_map<K, V>& a_rSender);
}

#include "CFunc+WinAPI_Abs.inl"
