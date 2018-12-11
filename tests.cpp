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
	testBlock(string title, std::initializer_list<test*> tests)
	{
		this->title = title;
		this->tests = tests;
	}
	testBlock(string title, std::initializer_list<fn> tests)
	{
		this->title = title;
		for(auto iter = tests.begin(); iter != tests.end(); iter++)
		{
			this->tests.push_back(new test(*iter));
		}
	}

	string title;
	vector<test*> tests;

	void run(int position)
	{
		for(int i = 0; i < tests.size(); i++)
		{
			tests[i]->run(title, position, i);
		}

	}
};

vector<testBlock*> blocks = 
{
	new testBlock("smartArrays class tests",
		{

			//Makes sure that a smartArrays' internal size is zero when using the default constructor
			new test([]{
				var::smartArray<int> arr;
				if (arr.size() != 0) return "smartArray.size() is not 0 when created using the default constructor!";

				return ""; 
			}),

			//Makes sure that the begin() and end() iterators refer to the correct positions
			new test([]{
				var::smartArray<int> arr;

				if (arr.begin() + arr.size() != arr.end()) return "smartArray.end() does not return the proper position (relative to smartArray.begin()) -- arr.begin() + arr.size() should equal arr.end())";

				return "";
			}),

			//Makes sure the size constructor works properly
			new test(
				"Size constructor testing",
				[] {
					var::smartArray<int> arr(5);

					if(arr.size() != 5) return "smartArray.size() does not equal the size of the input array!";

					return "";
				}
			),

			//Makes sure the size constructor allocates memory properly
			new test(
				"Size constuctor testing - memory allocation testing",
				[] {
					var::smartArray<int> arr(5);
					
					arr[0] = 1;
					arr[4] = 7;

					try
					{
						arr[5] = 8;
						return "smartArray::operator[] allowed access to elements past the end of the array!";
					}
					catch(var::smArrOutOfBoundsException e)
					{
						//We expect this exception
					}
					catch(...)
					{
						return "smartArray::operator[] (for an index outside of bounds) threw an unknown exception!";
					}

					return "";
				}
			),

			//Makes sure the array constructor does not throw exceptions
			new test(
				"Array constructor testing - no-exception testing",
				[] {
					int normal[] = { 1, 2, 3, 4, 5 };

					try
					{
						var::smartArray<int> arr(normal, sizeof(normal));
					}
					catch(var::Exception e)
					{
						return "smartArray::smartArray(array) threw a zlib exception with details:" + e.details;
					}
					catch(...)
					{
						return string("smartArray::smartArray(array) threw an unknown exception!");
					}

					return string("");
				}
			),

			//Makes sure the array constructor copies the source array, and doesn't get a reference to it
			new test(
				"Array constructor testing - argument copy testing",
				[]{				
					int * source = new int[5] {0, 1, 2, 3, 4};

					var::smartArray<int> arr(source, sizeof(source));

					for(int i = 0; i < 5; i++)
					{
						if(arr[i] != i) return "Values were not copied into the array correctly!";
					}
					
					delete source;

					for(int i = 0; i < 5; i++)
					{
						if(arr[i] != i) return "The array in the constructor were not copied!";
					}
										
					return "";
				}
			),

			//Makes sure the iterator starts at the beginning
			new test(
				"smartArray::smartArray(initializer_list)",
				[]{
					var::smartArray<int> arr = {0, 1, 2, 3, 4};
					
					for(int i = 0; i < 5; i++)
					{
						if(arr[i] != i) return "smartArray values incorrect";
					}
					
					return "";
				}
			),
			
			//Tests smartArray iterators
			new test(
				"smartArray iterator test",
				[]{
					var::smartArray<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};

					if( *arr.begin() != 0) return "Iterator starts at incorrect location!";
					int expected = 0;
					for(auto iter = arr.begin(); iter != arr.end(); iter++)
					{
						if(expected == 9) return "Iterator error - iterator went too far!";
						if(*iter != expected) return "Iterator error - unexpected value!";
						expected++;
					}

					return "";
				}
			)
		}
	)
};

int main(int argc, char * argv[])
{
	cout << "Beginning tests." << endl;
	
	//Launch the tests
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->run(i);
	}


	cout << "Tests complete." << endl;
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
