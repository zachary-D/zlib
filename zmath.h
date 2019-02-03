#pragma once

//Written by and copyright Zachary Damato
//zmath.h is part of the zlib submodule
#include <math.h>
#include <vector>

namespace zlib
{
	namespace math
	{
		const double pi = 4 * std::atan(1);

		std::vector<int> factor(int value);	//Returns a vector composed of the smallest factors of value

	}

}