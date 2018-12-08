#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;

#include "zlib.h"

typedef std::function<string()> fn;

vector<fn> test_var_smartArray = {

	//Makes sure that a smartArrays' internal size is zero when using the default constructor
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


vector<vector<fn> * > tests = 
{
	&test_var_smartArray
};


int main(int argc, char * argv[])
{
	cout << "Beginning tests." << endl;

	vector<std::function<string()>> tests =
	{
	
	};
	
	int numFailed = 0;
	//Launch the tests
	for (int testSet = 0; testSet < tests.size(); testSet++)
	{
		for(int i = 0; i < *(tests[testSet]).size(); i++)
		{
			try
			{
				string result = *(tests[testSet]).[i]();

				if (result != "")
				{
					cout << "FAILED-" << i << ": " << result << endl;
					numFailed++;
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
	}


	cout << "Ending tests." << endl;
	cout << "Total tests : " << tests.size() << endl;
	cout << "Tests failed: " << numFailed << endl;
	cout << "Tests passed: " << (tests.size() - numFailed) << endl;

	if(numFailed > 0)
	{
		cout << "<<TESTS FAILED!>>" << endl;
		return 1;
	}	

	return 0;
}


			string test1() {

			
		}

		string test2() {

		}
