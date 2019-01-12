#pragma once

//Written by and copyright Zachary Damato
//math.cpp is part of the zlib submodule

#include <vector>

namespace zlib
{
	namespace math
	{
		std::vector<int> factor(int value)
		{
			std::vector<int> result;

			//If the value is 0, the factor is 0 (sort of, probably techically wrong)
			if(value == 0) return std::vector<int>{0};

			if(value < 0)	//If the value is negative, add -1 to the factors and change it to positive
			{
				result.push_back(-1);
				value *= -1;
			}

			//Check if every number from 2 to the value to see if it is a factor
			for(int i = 2; i <= value; i++)
			{
				//Factor out the current number as many times as possible
				while(value % i == 0)
				{
					result.push_back(i);
					value /= i;
				}
			}

			return result;

		}
	}
}