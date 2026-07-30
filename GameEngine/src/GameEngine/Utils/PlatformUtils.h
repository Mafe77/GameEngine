#pragma once

#include <string>

namespace GameEngine
{
	class FileDialogs
	{
	public:
		// returns empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}