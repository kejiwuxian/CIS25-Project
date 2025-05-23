#pragma once

#include <string>	// For string
#include <map>

using namespace std;

namespace UnitPriceCalculator
{
	class Currency
	{
	public:
		static map<string, string> currencies;

	private:
		inline static const string exchange_api_base = "https://latest.currency-api.pages.dev/v1/";

		string value;

	public:
		Currency();

		Currency(const string& currency);

		string& operator=(const string& currency);

		static void init();

		static bool is_valid(const string& currency);

		static string get_description(const string& currency);

		static double get_conversion_rate(const string& from, const string& to);

		bool is_valid() const;

		string get_name() const;

		string get_description() const;

		double get_conversion_rate(const string& to) const;
	};
}