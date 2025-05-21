#pragma once

#include <string>	// For string

using namespace std;

namespace UnitPriceCalculator
{
	class CURL
	{
	public:
		static string fetch(const string& url);
	};
}