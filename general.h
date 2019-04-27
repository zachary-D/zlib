#pragma once

#include "var.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
	

	//Calculates a checksum of `checksum_length` bytes from the array `data` of length `data_length` bytes
	void calculateChecksum(var::byte * data, unsigned data_length, var::byte * checksum, unsigned checksum_length);
}