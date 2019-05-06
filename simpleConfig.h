#include<string>
#include<exception>
using std::string;

namespace zlib
{
	namespace simpleConfig
	{
		struct simpleConfig_error : std::exception
		{
			const char * what() const throw()
			{
				return "Catch-all simpleConfig error";
			}
		};

		struct key_not_found_error : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "Key not found";
			}
		};

		struct string_not_int_error : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "The value was requested as an integer, but the value is actually a string";
			}
		};

		struct int_not_string_error : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "The value was requested as a string, but the value is actually an integer";
			}
		};

		struct file_location_does_not_exist : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "The filename specified does not exist";
			}

		};

		struct file_cannot_be_written : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "There was an error opening that file for writing";
			}
		};

		struct file_cannot_be_read : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "Cannot read from file";
			}
		};

		struct file_malformed : simpleConfig_error
		{
			const char * what() const throw()
			{
				return "The config file is malformed and cannot be parsed";
			}
		};

		//A group of config keys
		struct simpleConfigGroup
		{
			//Creates an empty config group
			simpleConfigGroup() {}
			//Loads a config group from a file
			simpleConfigGroup(string filePath);
		private:
			//The file the config was loaded from, if applicable
			string loadedFrom = "";

			std::vector<std::pair<string, string>> strValues;
			std::vector<std::pair<string, int>> intValues;

		public:
			//Self-explanatory tests
			bool isKeyString(string key);
			bool isKeyInt(string key);
			bool doesKeyExist(string key);

			//Get the value of a key that has a string value 
			string get(string key);
			
			//Get the value of a key that has a int value
			int getInt(string key);

			//Sets the value associated with a key
			void set(string key, string value);
			void set(string key, int value);

			//Saves the config to a file.  Overwrites the file it was loaded from if blank.
			void save(string path = "");
		};
	}
}