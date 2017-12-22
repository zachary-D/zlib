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
			fileNotFound,	//If the file wasn't found (reading)
			fileClosed,
			endOfFile,

			fileNotOpened,	//If the file couldn't be opened for wiriting
		};

		class fileReader		//A wrapper to read from a file.  Throws exceptions to signify file not found/file ended/unable to read datatype/etc.
		{
			std::ifstream file;
			bool fileClosed = false;

		public:
			void open(std::string _file);		//Opens the file for reading, preforming checks on the filename
			void openRaw(std::string _file);	//Opens the file for reading, not preforming any checks on the filename given
			void close();

			char getChar();
			std::string getLine();
			std::vector<std::string> getEntireFile();

			void checkFileStatus();

			/*
			//These functions read data from the file and store it as the given datatype.  An exception is raised if the data read from the file does not match the format expected
			//They expect the 'ZML' format
			var::color_RGB readColorRGB();
			var::coord2 readCoord2();
			var::fraction readFraction();
			var::mVector readMVector();
			var::geom::circle readCircle();
			var::geom::line readLine();
			var::geom::square readSquare();
			*/
		};

		class fileWriter
		{
			std::ofstream file;
			bool fileClosed = false;
			bool firstLine = true;		//Used to make sure we don't put an endl at the beginning of the file automatically

		public:
			void open(std::string _file);		//Opens the file for writing, preforming checks on the filename
			void openRaw(std::string _file);	//Opens the file for writing, not preforming any checks on the filename given
			void close();

			void writeRaw(char value);
			void writeRaw(std::string value);
			void writeEndLine() { file << std::endl; }
			
			void write(std::string value);
			void write(int value);

			/*
			//These functions write data to the file in the ZML format
			void write(var::color_RGB value);
			void write(var::coord2 value);
			void write(var::fraction value);
			void write(var::mVector value);
			void write(var::geom::circle value);
			void write(var::geom::line value);
			void write(var::geom::square value);
			*/
		};
	}
}