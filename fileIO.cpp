#pragma once

#include <iostream>

#include "fileIO.h"

namespace zlib
{
	namespace fileIO
	{
		void fileReader::open(std::string _file, bool appendExtension)
		{
			file.open(_file + (appendExtension ? ".zml": ""));

			if(!file) throw fileErrors::fileNotFound;
		}
	}
}