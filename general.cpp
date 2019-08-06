#pragma once
#include <chrono>	//std::chrono::high_resolution_clock
#include <cmath>

#include "general.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
	void calculateChecksum(var::byte * data, unsigned data_length, var::byte * checksum, unsigned checksum_length)
	{
		//Argument-checking
		if(data_length == 0)
		{
			//throw exception - cannot have 0-length checksum
		}

		if(data == NULL)
		{
			//Exception - null pointer
		}

		if (checksum == NULL)
		{
			//Exception - bad output
		}

		
		//Initialize the array
		for(unsigned i = 0; i < checksum_length; i++)
		{
			checksum[i] = 0b0;
		}

		//Actually calculate the checksum
		for(unsigned pos = 0; pos < data_length; pos++)
		{
			int a = pos % checksum_length;
			var::byte first = checksum[pos % checksum_length];
			var::byte second = data[pos];
			var::byte result = first ^ second;
			checksum[pos % checksum_length] ^= data[pos];
		}
	}

	bool validateChecksum(var::byte * data, unsigned data_length, var::byte * expectedChecksum, unsigned checksum_length)
	{
		var::byte * checksum = new var::byte[checksum_length];

		calculateChecksum(data, data_length, checksum, checksum_length);

		for(unsigned i = 0; i < checksum_length; i++)
		{
			if(expectedChecksum[i] != checksum[i]) return false;
		}

		return true;
	}
}
