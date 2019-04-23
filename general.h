#pragma once

#include <chrono>	//std::chrono::high_resolution_clock

#include "var.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
	//Tracks the amount of time since its creation, with ns precision
	class timer
	{
	public:
		timer();

	private:
		std::chrono::high_resolution_clock::time_point begin;

	public:
		double getTime();	//Returns the time in seconds since the creation of the timer
		long long int getRaw();	//Returns the time in ns
	};

	//Calculates a checksum of `checksum_length` bytes from the array `data` of length `data_length` bytes
	var::t_byte * calculateChecksum(t_byte * data, unsigned data_length, unsigned checksum_length);
}