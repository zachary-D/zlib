#pragma once

#include <fstream>
#include <string>

#include "varTypes.h"

namespace zlib
{
	namespace fileIO
	{
		enum class fileErrors
		{
			fileNotFound,
		};

		class fileReader		//A wrapper to read from a file.  Throws exceptions to signify file not found/file ended/unable to read datatype/etc.
		{
			std::ifstream file;

		public:
			void open(std::string _file, bool appendExtension = true);

			char getChar();
			std::string getLine();
			std::vector<std::string> getEntireFile();

			//These functions read data from the file and store it as the given datatype.  An exception is raised if the data read from the file does not match the format expected
			//They expect the 'ZML' format
			var::color_RGB readColorRGB();
			var::coord2 readCoord2();
			var::fraction readFraction();
			var::mVector readMVector();
			var::geom::circle readCircle();
			var::geom::line readLine();
			var::geom::square readSquare();
		};

		class fileWriter
		{
			std::ofstream file;

		public:
			void open(std::string _file, bool appendExtension = true);

			void writeRaw(char value);
			void writeRaw(std::string value);

			void write(var::color_RGB value);
			void write(var::coord2 value);
			void write(var::fraction value);
			void write(var::mVector value);
			void write(var::geom::circle value);
			void write(var::geom::line value);
			void write(var::geom::square value);
		};
	}
}