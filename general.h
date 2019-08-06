#pragma once

#include "var.h"

//So we can assume zlib is the namespace incase we need to pull things from other zlib files
namespace zlib {}
using namespace zlib;

namespace zlib
{
	

	//Calculates a checksum of `checksum_length` bytes from the array `data` of length `data_length` bytes
	void calculateChecksum(var::byte * data, unsigned data_length, var::byte * checksum, unsigned checksum_length);

	//Calculates the checksum for `data` of length `data_length` bytes, and compares it to a checksum `expectedChecksum` of length `checksum_length`, and returns true if they match, and false otherwise
	bool validateChecksum(var::byte * data, unsigned data_length, var::byte * expectedChecksum, unsigned checksum_length);
}