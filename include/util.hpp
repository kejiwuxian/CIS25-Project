#pragma once

#include <string>	// For string

using namespace std;

namespace UnitPriceCalculator
{
	class Util
	{
	public:
		// Removes leading, and trailing whitespaces, \r and \n then convert to lowercase
		static void strip_and_to_lower(string& str);

		// Get a single character without waitting for enter
		static char getch();

		// Clear console window
		static void clear_console();
	};
}