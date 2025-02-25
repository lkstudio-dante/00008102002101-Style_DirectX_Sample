#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"
#include "CFunc+C_Abs.h"

#include "CFunc+Cpp_Map.h"
#include "CFunc+Cpp_File.h"

namespace CFunc
{
	/** 리소스를 제거한다 */
	template<typename T>
	void FreeResources(std::vector<T>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename K, typename V>
	void FreeResources(std::unordered_map<K, V>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename T>
	void DeleteResources(std::vector<T>& a_rSender);

	/** 리소스를 제거한다 */
	template<typename K, typename V>
	void DeleteResources(std::unordered_map<K, V>& a_rSender);
}

#include "CFunc+Cpp_Abs.inl"
