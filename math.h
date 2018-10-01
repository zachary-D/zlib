#pragma once

//Written by and copyright Zachary Damato
//math.h is part of the zlib submodule
#ifdef __linux__
#include <math.h>	//Hopefully won't conflict with the name of this file, required for atan() on linux
#endif
#include <vector>

namespace zlib
{
	namespace math
	{
		const double pi = 4 * atan(1);

		std::vector<int> factor(int value);	//Returns a vector composed of the smallest factors of value

	}

}