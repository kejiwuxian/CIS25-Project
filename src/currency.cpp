#include <stdexcept>// For runtime_error

#include "currency.hpp"
#include "curl.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	map<string, string> Currency::currencies;

	Currency::Currency() : value{ "" }
	{
		if (currencies.empty())
		{
			init();
		}
	}

	Currency::Currency(const string& currency) : value{ currency }
	{
		if (currencies.empty())
		{
			init();
		}
	}

	string& Currency::operator=(const string& currency) { return value = currency; }

	void Currency::init()
	{
		currencies.clear();
		string res = CURL::fetch(exchange_api_base + "currencies.min.json");

		size_t i = res.find("\"");
		while (i >= 0 && i < res.length())
		{
			size_t sep = res.find(":", i);
			string name = res.substr(i + 1, sep - i - 2);
			i = res.find("\"", sep + 2);
			currencies[name] = res.substr(sep + 2, i - sep - 2);
			i += 2;
		}
	}

	bool Currency::is_valid(const string& currency)
	{
		if (currencies.empty())
		{
			init();
		}

		return currencies.count(currency);
	}

	string Currency::get_description(const string& currency)
	{
		if (!is_valid(currency))
		{
			throw runtime_error("Error: Invalid currency");
		}

		return currencies[currency];
	}

	double Currency::get_conversion_rate(const string& from, const string& to)
	{
		if (from == to)
		{
			return 1;
		}

		string res = CURL::fetch(exchange_api_base + "currencies/" + from + ".min.json");

		try
		{
			size_t s = res.find("\"" + to + "\":");	// Find the start of name/value pairs
			s += to.length() + 3;					// Skip the name
			size_t e = res.find(",", s);			// Find the end of the name/value pairs
			return stod(res.substr(s, e - s));		// Convert the value to double
		}
		catch (exception)
		{
			throw runtime_error("Error: Failed to process fetched exchange rate");
		}
	}

	bool Currency::is_valid() const { return is_valid(value); }

	string Currency::get_name() const { return value; }

	string Currency::get_description() const { return get_description(value); }

	double Currency::get_conversion_rate(const string& to) const { return get_conversion_rate(value, to); }
}