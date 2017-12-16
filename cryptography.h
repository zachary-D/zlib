#pragma once

//Written by and copyright Zachary Damato
//cryptography.cpp is part of the zlib submodule

#ifdef USING_ZLIB_CRYPTO

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace zlib {} //This is here so we can set the using namespace below, so that if we need to include another file from zlib the zlib namespace will already be assumed

using namespace zlib;

namespace zlib
{
	namespace crypto
	{
		//Note: the following functions do not ignore any characters (including \n) and, as a rule of thumb, sanitize() used to be convert encoded data for output to the console, and desanitize() should be used to convert data from the console into strings for use internally
		string sanitize(string & data, bool modifyArgument = false);		//Convers data from a string (which may or may not contain invisible characters) to a string where all characters are visible. (invisible character -> `KEYCODE).  If modifyArgument is true, 'data' will be modified to be sanitized (equal to data = sanitize(data))
		//string desanitize(string & data);		//Undoes sanitize().  Converts invisble characters from `KEYCODE format to their normal form

		namespace cipher
		{
			namespace caesar		//Encodes data using a caesar cipher
			{
				string encode(string data, int shiftValue = 12);
				string decode(string data, int shiftValue = 12);
			}

			/*namespace caesar_numerical
			{
				string encode(vector<int> data, int shiftValue = 12);
				string encode(string data, int shiftValue = 12);
				string decode(vector<int> data, int shiftValue = 12);
				string decode(string data, int shiftValue = 12);
			}*/

			namespace numerical		//Encodes data by converting it to ASCII key-codes
			{
				string encode(string data);		//Encodes a string, into numerical codes, and returns the data string
				string decode(vector<int> data);	//Decodes an integer vector, and returns the decoded string
				string decode(string data);		//Decodes a string using 'shiftValue', and returns the decoded string
			}

			namespace vignere		//Encodes data using a vignere cipher
			{
				string encode(string data, string key);		//Encodes 'data' using 'key'
				string decode(string data, string key);		//Decodes 'data' using 'key'
			}
		}
	}
}

#endif