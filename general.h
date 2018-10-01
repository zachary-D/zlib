#pragma once

#include <chrono>	//std::chrono::high_resolution_clock

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
	};
}