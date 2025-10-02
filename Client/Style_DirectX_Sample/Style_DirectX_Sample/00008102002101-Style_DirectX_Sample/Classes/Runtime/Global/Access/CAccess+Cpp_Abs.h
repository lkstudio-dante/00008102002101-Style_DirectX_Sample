#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

#include "CAccess+Cpp_Vector.h"
#include "CAccess+Cpp_Map.h"

namespace CAccess
{
	/** 파일 이름을 반환한다 */
	std::string GetName_File(const std::string& a_rPath_File,
		bool a_bIsInclude_Extension = true);

	/** 파일 확장자를 반환한다 */
	std::string GetExtension_File(const std::string& a_rPath_File);
}
