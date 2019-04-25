#pragma once
#include <chrono>	//std::chrono::high_resolution_clock
#include <cmath>

#include "general.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
		var::byte * calculateChecksum(var::byte * data, unsigned data_length, unsigned checksum_length)
		{
		//Argument-checking
		if(data_length = 0)
		{
			//throw exception - cannot have 0-length checksum
		}

		if(data == NULL)
		{
			//Exception - null pointer
		}

		var::byte * ret;

		try
		{
			ret = new var::byte[checksum_length];
		}
		catch(...)
		{
			//If we were unable to create an array of size `checksum_length`
			throw 1;	//need to change to an actual exception
		}

		//Initialize the array
		for(unsigned i = 0; i < checksum_length; i++)
		{
			ret[i] = 0b0;
		}
		//Actually calculate the checksum
		for(unsigned pos = 0; pos < data_length; pos++)
		{
			ret[pos & checksum_length] ^= data[pos];
		}

		return ret;
	}
}
