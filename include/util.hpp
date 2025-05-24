#pragma once

#include <string>	// For string
#include <cctype>	// For tolower

using namespace std;

namespace UnitPriceCalculator
{
	class Util
	{
	public:
		// Removes leading, and trailing whitespaces, \r and \n then convert to lowercase
		static void strip_and_to_lower(string& str);
	};
}