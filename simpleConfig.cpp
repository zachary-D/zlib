#include <string>
#include <vector>
#include <exception>

using std::string;

#include "var.h"

#include "simpleConfig.h"

namespace zlib
{
	namespace simpleConfig
	{
		bool simpleConfigGroup::isKeyString(string key)
		{
			for (auto & iter : strValues) if (iter.first == key) return true;
			return false;
		}

		bool simpleConfigGroup::isKeyInt(string key)
		{
			for (auto & iter : intValues) if (iter.first == key) return true;
			return false;
		}

		bool simpleConfigGroup::doesKeyExist(string key)
		{
			return isKeyString(key) || isKeyInt(key);
		}

		string simpleConfigGroup::get(string key)
		{
			//Try to retrieve the value from the list of string-values
			for (auto & iter : strValues) if (iter.first == key) return iter.second;

			//If we can't find the key in the string-values, check to see if it's in the int-values to throw the proper error
			for (auto & iter : intValues) if (iter.first == key) throw int_not_string_error();

			throw key_not_found_error();
		}

		int simpleConfigGroup::getInt(string key)
		{
			//Try to retrieve the value from the list of int-values
			for (auto & iter : intValues) if (iter.first == key) return iter.second;

			//If we can't find the key in the int-values, check to see if it's in the string-values to throw the proper error
			for (auto & iter : strValues) if (iter.first == key) throw string_not_int_error();

			throw key_not_found_error();
		}

		void simpleConfigGroup::set(string key, string value)
		{
			//If the key already exists, update it
			for (auto & iter : strValues) if (iter.first == key) iter.second = value;

			//If the key does not exist, check if it exists in the int-list
			if (isKeyInt(key)) throw int_not_string_error();

			//Otherwise create the pair
			strValues.push_back(std::pair<string, string>(key, value));
		}

		void simpleConfigGroup::set(string key, int value)
		{
			//If the key already exists, update it
			for (auto & iter : intValues) if (iter.first == key) iter.second = value;

			//If the key does not exist, check if it exists in the int-list
			if (isKeyString(key)) throw string_not_int_error();

			intValues.push_back(std::pair<string, int>(key, value));
		}
	}
}