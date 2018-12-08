#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;

#include "zlib.h"

int main(int argc, char * argv[])
{
	cout << "Beginning tests." << endl;

	vector<std::function<string>> tests =
	{
		[]{
			var::smartArray<int> arr;

			if (arr.size() != 0) return "smartArray.size() is not 0 when created using the default constructor!";

			return ""; 
		},

		[]{
			var::smartArray<int> arr;

			if (arr.begin() + arr.size() + 1 != arr.end()) return "smartArray.end() does not return the proper position (relative to smartArray.begin()) - arr.begin() + arr.size() + 1 should equal arr.end())";

			return "";
		}
	};
	
	int numFailed = 0;

	for (int i = 0; i < tests.size(); i++)
	{
		try
		{
			string result = tests[i]();

			if (result != "")
			{
				cout << "Test " << i << " failed with message: " << result << endl;
			}
		}
		catch (var::Exception e)
		{
			cout << "Caught zlib::Exception from test " << i << "!" << endl;
			if(e.details != "") cout << "Exception.details = " << e.details << endl;
			numFailed++;
		}
		catch (...)
		{
			cout << "Caught exception from test " << i << "!" << endl;
			numFailed++;
		}
	}

	
	cout << "Ending tests." << endl;
	return 0;
}


		void test_smartArray()
		{
			cout << "Starting test for smartArray"
			vector<string> result;
			auto exec = [&result](string testResult)
			{
				result.push_back(testResult);
			};

			vector<std::function<string>> tests =
			{
				[exec]() {



				};


			}

			exec(test1());
			exec(test2());




			for (int i = 0; i < result.size(); i++)
			{
				if (result[i] == "") std::cout << "Test " << i << " passed" << std::endl;
			}
		}


		//Makes sure that a smartArrays' internal size is zero when using the default constructor
		string test1() {

			
		}

		string test2() {

		}
