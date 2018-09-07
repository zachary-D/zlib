#pragma once
#include <chrono>	//std::chrono::high_resolution_clock
#include <cmath>

#ifndef makefile
#include "zlib/general.h"
#else
#include "general.h"
#endif

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
}
