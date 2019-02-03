#include <string>

using std::string;

#include "var.h"

namespace zlib {}
using namespace zlib;

#include "textUtils.h"

namespace zlib
{
	namespace textUtils
	{
		string const getMatching(string first, string second, const std::byte modifiers)
		{
			//Check bit corresponding to IGNORE_CASE
			if ((modifiers & IGNORE_CASE) != NO_MOD)
			{
				first = conv::toLowercase(first);
				second = conv::toLowercase(second);
			}

			for (int i = 0; i < first.length() && i < second.length(); i++)
			{
				if (first[i] != second[i])
				{
					return first.substr(0, i);
				}
			}

			if (first.length() > second.length()) return second;
			return first;
		}

		string const getMatchingRight(string first, string second, const std::byte modifiers)
		{
			//Check bit corresponding to IGNORE_CASE
			if ((modifiers & IGNORE_CASE) != NO_MOD)
			{
				first = conv::toLowercase(first);
				second = conv::toLowercase(second);
			}

			for (int i = 0; i < first.length() && i < second.length(); i++)
			{
				if (first[first.length() - i] != second[second.length() - i])
				{
					return first.substr(first.length() - i + 1);
				}
			}

			if (first.length() > second.length()) return second;
			return first;
		}
	}
}