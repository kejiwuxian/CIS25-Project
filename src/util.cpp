#include "util.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	// Removes leading, and trailing whitespaces, \r and \n then convert to lowercase
	void Util::strip_and_to_lower(string& str)
	{
		// Strip Left
		while (!str.empty() && string(" \r\n").find(str[0]) != string::npos)
		{
			str.erase(0, 1);
		}

		// Strip Right
		while (!str.empty() && string(" \r\n").find(str[str.length() - 1]) != string::npos)
		{
			str.pop_back();
		}

		// To Lower
		for (size_t i = 0;i < str.length();i++)
		{
			str[i] = tolower(str[i]);
		}
	}
}