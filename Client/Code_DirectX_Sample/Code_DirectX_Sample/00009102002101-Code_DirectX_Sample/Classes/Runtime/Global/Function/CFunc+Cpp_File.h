#pragma once

#include "../Define/KCDefine+Cpp_Abs.h"

namespace CFunc
{
	/** 디렉토리를 순회한다 */
	void EnumerateDirectories(const std::string& a_rPath_Dir,
		const std::function<void(std::filesystem::path)>& a_rCallback);
}
