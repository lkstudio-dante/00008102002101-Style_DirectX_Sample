#include "CAccess+Cpp_Abs.h"

namespace CAccess
{
	std::string GetName_File(const std::string& a_rPath_File, bool a_bIsInclude_Extension)
	{
		std::filesystem::path oPath(a_rPath_File);
		auto oName_File = oPath.filename();

		return (a_bIsInclude_Extension || !oName_File.has_extension()) ?
			oName_File.string() : oName_File.replace_extension(::G_STR_EMPTY).string();
	}

	std::string GetExtension_File(const std::string& a_rPath_File)
	{
		std::filesystem::path oPath(a_rPath_File);
		return oPath.has_extension() ? oPath.extension().string() : ::G_STR_EMPTY;
	}
}
