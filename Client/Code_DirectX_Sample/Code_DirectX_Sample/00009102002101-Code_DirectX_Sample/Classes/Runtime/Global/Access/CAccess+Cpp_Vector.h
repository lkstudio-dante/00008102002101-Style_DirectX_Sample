#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CAccess
{
	/** 인덱스 유효 여부를 검사한다 */
	template<typename T>
	bool IsValid_Idx(std::vector<T>& a_rSender, int a_nIdx);

	/** 값을 반환한다 */
	template<typename T>
	T GetVal(std::vector<T>& a_rSender, int a_nIdx, T a_tVal_Def);
}

#include "CAccess+Cpp_Vector.inl"
#include "CAccess+Cpp_Map.inl"
