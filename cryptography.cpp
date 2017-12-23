#pragma once

//Written by and copyright Zachary Damato
//cryptography.h is part of the zlib submodule

#ifdef USING_ZLIB_CRYPTO

#define debug

#include <string>
#include <vector>

#ifdef debug
#include <iostream>
#endif

using std::string;
using std::vector;

#ifdef debug
using std::cout;
using std::endl;
#endif

#include "varConv.h"

using namespace zlib;

namespace zlib
{
	namespace crypto
	{
		void sanitizeInternal(string & data)		//Sanitizes 'data' and stores the result in 'data'.  See header for sanitize() for an explanation on sanitization
		{
			/*
				Codes that need to be converted (inclusive):
				0 -> 31
				127-255
				therefore valid characters are (inclusive):
				32-126
			*/

			string output;

			for(auto iter = data.begin(); iter != data.end(); iter++)
			{
				//Check to see if the character is valid
				if(*iter == '`')
				{
					//Grave is used as to specify a keycode when used on its own, so we need to escape it
					output += "``";
				}
				else if(32 <= *iter && *iter <= 126)
				{
					//Valid characters
					output += *iter;
				}
				else
				{
					//Invalid characters
					output += ("`" + conv::toString((int) *iter));
				}
			}



		}

		string sanitize(string & data, bool modifyArgument)		//See header
		{
			if(modifyArgument)
			{
				sanitizeInternal(data);
				return data;
			}
			else
			{
				string _data = data;	//copy values from 'data' to '_data' so 'data' remains unchanged
				sanitizeInternal(_data);
				return _data;
			}
		}

		inline void desanitizeInternal(string & data)
		{
			int lastPos = 0;		//The point to search after (set when a ` is modified, so it doesn't get picked up again)
			int gravePos = data.find('1', lastPos);	//The position of `
			while(gravePos != string::npos)
			{
				//Convert `KEYCODEs to chars
			}
		}

		namespace cipher
		{
			namespace caesar		//A standard caesar cipher
			{
				string encode(string data, int shiftValue)		//Encodes a string using 'shiftValue', and returns the encoded string 
				{
					string output;
					for(int i = 0; i < data.length(); i++)
					{
						//char(int) tops out at 255, at which point it wraps around, so we don't need to deal with modulus.  Perfect!
						output.push_back(char(data[i] + shiftValue));
					}
					return output;
				}

				string decode(string data, int shiftValue)		//Decodes a string using 'shiftValue', and returns it.  (Basically just runs the encode function in reverse)
				{
					return encode(data, -1 * shiftValue);
				}
			}

			/*namespace caesar_numerical		//A caesar cipher that returns data as a set of integers corresponding to chars
			{
				string encode(vector<int> data, int shiftValue)		//Encodes an integer vector using 'shiftValue', and returns the encoded string produced
				{
					string output;	//A string containing the encoded data
					for(int i = 0; i < data.size(); i++)	//Loop over the entire vector
					{
						//Shift the value according to the cipher
						int value = data[i] + shiftValue;

						//Make sure the value isn't out of bounds, wrapping if necessary
						if(value < 0) value += 256;
						if(value > 255) value -= 256;

						//Append 0's to the value if necessary so that the data is 3 characters in length
						if(0 <= value && value <= 9) output += "00";
						if(10 <= value && value <= 99) output += "0";

						//Append the newly encoded data to the data string
						output += conv::toString(value);
					}
					return output;
				}

				string encode(string data, int shiftValue)		//Encodes a string using 'shiftValue', returning the encoded string
				{
					//Convert the string into an integer vector
					vector<int> _data;
					for(int i = 0; i < data.length(); i++)
					{
						_data.push_back(data[i]);
					}
					//Pass the integer vector through the encoding function, and return it
					return encode(_data, shiftValue);
				}

				string decode(vector<int> data, int shiftValue)		//Decodes an integer vector using 'shiftValue', and returns the decoded string
				{
					string output;
					//Loop over every item in the vector, apply the 'shiftValue', convert it to a char, and append it to the output
					for(int i = 0; i < data.size(); i++)
					{
						output += char(data[i] - shiftValue);
					}
					return output;
				}

				string decode(string data, int shiftValue)			//Decodes a string using 'shiftValue', and returns the decoded string
				{
					vector<int> extracted_data;
					//Loop over every character in the string, converting them to an integer and appending them to the 'extracted_data' vector
					for(int i = 0; i < data.length(); i += 3)
					{
						string extracted = data.substr(i, 3);
						extracted_data.push_back(conv::toNum(extracted));
					}
					//Pass the extracted data through the decoding function
					return decode(extracted_data, shiftValue);
				}
			}*/

			namespace numerical	//Convers characters to their 3-digit key code
			{
				string encode(string data)		//Encodes a string, into numerical codes, and returns the data string
				{
					string output;	//A string containing the encoded data
					for(int i = 0; i < data.size(); i++)	//Loop over the entire vector
					{
						//Convert the character to an integerw
						int value = data[i];

						//Append 0's to the value if necessary so that the data is 3 characters in length
						if(0 <= value && value <= 9) output += "00";
						else if(10 <= value && value <= 99) output += "0";

						//Append the newly encoded data to the data string
						output += conv::toString(value);
					}
					return output;
				}

				string decode(vector<int> data)		//Decodes an integer vector, and returns the decoded string
				{
					string output;
					//Loop over every item in the vector, convert it to a char, and append it to the output
					for(int i = 0; i < data.size(); i++)
					{
						output += char(data[i]);
					}
					return output;
				}

				string decode(string data)		//Decodes a string using 'shiftValue', and returns the decoded string
				{
					vector<int> extracted_data;
					//Loop over every character in the string in sets of 3, converting them to an integer and appending them to the 'extracted_data' vector
					for(int i = 0; i < data.length(); i += 3)
					{
						string extracted = data.substr(i, 3);
						extracted_data.push_back(conv::toNum(extracted));
					}
					//Pass the extracted data through the decoding function, and return it
					return decode(extracted_data);
				}
			};

			namespace vignere	//See header
			{
				char encodeCharacter(char data, char key)	//Encodes a character 'data' given 'key'
				{
					return data + key - 2;
				}

				char decodeCharacter(char data, char key)	//Decodes a character 'data' given 'key'
				{
					return data - key + 2;
				}

				string encode(string data, string key)		//See header
				{
					string output;		//The encoded data

					for(int i = 0; i < data.length(); i++)		//Loops over each character
					{
						//Encodes each character, and appends it to the output string
						output += encodeCharacter(data[i], key[i%key.length()]);
					}

					return output;
				}

				string decode(string data, string key)		//See header
				{
					string output;		//The decoded data

					for(int i = 0; i < data.length(); i++)		//Loops over each character
					{
						//Decodes each character, and appends it to the output string
						output += decodeCharacter(data[i], key[i%key.length()]);
					}

					return output;
				}
			};
		}
	}
}

#endif