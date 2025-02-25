#include "CFunc+Cpp_File.h"

namespace CFunc
{
	void EnumerateDirectories(const std::string& a_rPath_Dir,
		const std::function<void(std::filesystem::path)>& a_rCallback)
	{
		for(auto& rDir : std::filesystem::recursive_directory_iterator(a_rPath_Dir))
		{
			a_rCallback(rDir.path());
		}
	}
}
