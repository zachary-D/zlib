#include <string>

using std::string;

namespace zlib {}
using namespace zlib;

namespace zlib
{
	namespace textUtils
	{
		//A default value used when no modifiers are specified
		const std::byte NO_MOD = std::byte(0);
		//performs the current operation ignoring case, treating A == a, B == b, etc.  Usually accomplished by converting the text to be compared to lowercase
		const std::byte IGNORE_CASE = std::byte(1);
		const std::byte CHANGE_ARGS = std::byte(1) << 1;	//Changes the arguments passed to the function to match the output (only where appopriate, i.e. trimSpaces)
		
		//Returns the string of characters that match in both strings, up until the first character that does not.  i.e. getMatching("ABCDEF", "ABCDQQ") would return "ABCD".  Note that if the IGNORE_CASE modifier is set all results will be returned in lowercase.
		string const getMatching(string first, string second, const std::byte modifiers = NO_MOD);
		//The same as getMatching() but working from right-to-left.  The text returned is NOT backwards.
		string const getMatchingRight(string first, string second, const std::byte modifiers = NO_MOD);

		string trimSpaces(string & str, std::byte modifiers = NO_MOD);
	}
}