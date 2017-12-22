#pragma once

#include <iostream>

#include "varConv.h"
#include "fileIO.h"

namespace zlib
{
	namespace fileIO
	{
		void fileReader::open(std::string _file)
		{
			if(_file.find('.') == string::npos)
			{
				_file = _file + ".txt";
			}
			file.open(_file);
			if(!file)
			{
				fileClosed = true;
				throw fileErrors::fileNotFound;
			}
		}

		void fileReader::openRaw(std::string _file)
		{
			file.open(_file);
			if(!file)
			{
				fileClosed = true;
				throw fileErrors::fileNotFound;
			}
			
		}
		
		void fileReader::close()
		{
			file.close();
			fileClosed = true;
		}

		char fileReader::getChar()
		{
			checkFileStatus();
			return file.get();
		}

		std::string fileReader::getLine()
		{
			checkFileStatus();
			string str;
			std::getline(file, str);
			return str;
		}

		std::vector<std::string> fileReader::getEntireFile()
		{
			std::vector<std::string> vec;

			while(!file.eof())
			{
				std::string str;
				std::getline(file, str);
				vec.push_back(str);
			}

			close();

			return vec;
		}

		void fileReader::checkFileStatus()
		{
			if(file.eof()) throw fileErrors::endOfFile;
			if(fileClosed) throw fileErrors::fileClosed;
		}

		
		void fileWriter::open(std::string _file)
		{
			if(_file.find('.') == string::npos)
			{
				_file += ".txt";
			}
			openRaw(_file);
		}

		void fileWriter::openRaw(std::string _file)
		{
			file.open(_file);
			if(!file)
			{
				fileClosed = true;
				throw fileErrors::fileNotFound;
			}
		}

		void fileWriter::close()
		{
			file.close();
			fileClosed = true;
		}

		void fileWriter::writeRaw(char value)
		{
			file << value;
			firstLine = false;
		}

		void fileWriter::writeRaw(std::string value)
		{
			file << value;
		}

		void fileWriter::write(std::string value)
		{
			file << value << std::endl;
		}

		void fileWriter::write(int value)
		{
			file << conv::toString(value) << std::endl;
		}
	}
}