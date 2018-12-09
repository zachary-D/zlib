#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::vector;

#include "zlib.h"

typedef std::function<string()> fn;

int numTests = 0;
int numFailed = 0;

template<class T>
string toString(T in)
{
	std::stringstream conv;
	conv << in;
	string out;
	conv >> out;
	return out;
}

//Returns the percentage 'val/of'
int getPercent(int val, int of)
{
	return round(100 * val / of);
}

string gPerc(int val, int of)
{
	return toString(getPercent(val, of)) + "%";
}

//A single test + its title
struct test
{
	test(fn _test)
	{
		this->_test = _test;
	}
	test(string title, fn _test)
	{
		this->title = title;
		this->_test = _test;
	}

	string title = "";
	fn _test;

	string run(string parentTitle, int parentPosition, int position)
	{
		auto pFailMsg = [&parentTitle, &parentPosition, &position, this] ()
		{
			cout << "FAILED <" << parentPosition << "|" << parentTitle << "::" << position << "|" << title << ">";
		};

		try
		{
			numTests++;
			string result = _test(); 

			if (result != "")
			{
				numFailed++;
				pFailMsg();
				cout << ": " << result << endl;
			}
		}
		catch (var::Exception e)
		{
			pFailMsg();
			cout << " - caught zlib exception!" << endl;
			if(e.details != "") cout << "\tException.details = " << e.details << endl;
			numFailed++;
		}
		catch (...)
		{
			pFailMsg();
			cout << " - caught generic exception!" << endl;
			numFailed++;
		}
	}
};

//A set of tests (related by topic, class, etc.)
struct testBlock
{
	testBlock(string title, std::initializer_list<test> tests)
	{
		this->title = title;
		this->tests = tests;
	}
	testBlock(string title, std::initializer_list<fn> tests)
	{
		this->title = title;
		for(auto iter = tests.begin(); iter != tests.end(); iter++)
		{
			this->tests.push_back(*iter);
		}
	}

	string title;
	vector<test> tests;

	void run(int position)
	{
		for(int i = 0; i < tests.size(); i++)
		{
			tests[i].run(title, position, i);
		}

	}
};

vector<testBlock> blocks = 
{
	testBlock("smartArrays class tests",
		{

			//Makes sure that a smartArrays' internal size is zero when using the default constructor
			[]{
				var::smartArray<int> arr;
				if (arr.size() != 0) return "smartArray.size() is not 0 when created using the default constructor!";

				return ""; 
			},

			//Makes sure that the begin() and end() pointers refer to the correct positions
			[]{
				var::smartArray<int> arr;

				if (arr.begin() + arr.size() != arr.end()) return "smartArray.end() does not return the proper position (relative to smartArray.begin()) - arr.begin() + arr.size() + 1 should equal arr.end())";

				return "";
			}
		}
	)
};

int main(int argc, char * argv[])
{
	cout << "Beginning tests." << endl;
	
	//Launch the tests
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].run(i);
	}


	cout << "Ending tests." << endl;
	cout << "Total tests : " << numTests << endl;
	cout << "Tests failed: " << numFailed << " (" << gPerc(numFailed, numTests) << ")" << endl;
	cout << "Tests passed: " << (numTests - numFailed) << " (" << gPerc(numTests - numFailed, numTests) << ")" << endl;

	if(numFailed > 0)
	{
		cout << "<<TESTS FAILED!>>" << endl;
		return 1;
	}	

	return 0;
}
