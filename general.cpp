#pragma once
#include <chrono>	//std::chrono::high_resolution_clock
#include <cmath>

#include "var.h"

#include "general.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
	timer::timer()
	{
		begin = std::chrono::high_resolution_clock::now();
	}

	double timer::getTime()
	{
		//The result is divided by 10^9 to convert from ns to s
		return (std::chrono::high_resolution_clock::now() - begin).count() / std::pow(10, 9);
	}

	long long int timer::getRaw()
	{
		return (std::chrono::high_resolution_clock::now() - begin).count();
	}

	var::t_byte * calculateChecksum(var::t_byte * data, unsigned data_length, unsigned checksum_length)
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

		var::t_byte * ret;

		try
		{
			ret = new var::t_byte[checksum_length];
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
