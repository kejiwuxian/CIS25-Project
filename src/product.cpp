#include <stdexcept>// For runtime_error
#include <cctype>	// For tolower
#include <sstream>	// For ostringstream

#include "product.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	// Removes leading, and trailing whitespaces, \r and \n then convert to lowercase
	void strip_and_to_lower(string& str)
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

	Product::Product() : name{ "" }, weight{ 0 }, unit{ Unit() }, price{ 0 }, currency{ Currency() }, unit_price{ 0 } {}

	Product::Product(const string& name, double price, const string& currency, double weight, const string& unit, double unit_price)
	{
		this->name = name;
		this->price = price;
		this->currency = Currency(currency);
		this->weight = weight;
		this->unit = Unit(unit);
		this->unit_price = unit_price;
	}

	Product::Product(const string& name, double price, const string& currency, double weight, const string& unit) : Product(name, price, currency, weight, unit, 0)
	{
		calc_unit_price();
	}

	Product::Product(const string& name, string price_tag, double unit_price)
	{
		this->name = name;

		// Process price
		strip_and_to_lower(price_tag);
		size_t i = price_tag.find_first_not_of("0123456789.-");	// Find the end of the price
		if (i == string::npos)									// When the end of the price is not found
		{
			throw runtime_error("Please enter a valid currency after the price");
		}
		string str = price_tag.substr(0, i);					// The string for the price
		if (str.empty())										// When the price is omitted by user
		{
			price = 1;											// Default to 1
		}
		else
		{
			try
			{
				price = stod(str);								// Convert the string for the price to double
				if (price <= 0)									// When the price entered is not a positive number
				{
					throw exception();
				}
			}
			catch (exception)
			{
				throw runtime_error("Please enter a valid positive number as price");
			}
		}
		price_tag = price_tag.substr(i);						// Skip the price

		// Process currency
		i = price_tag.find('/');								// Find the end of the currency
		if (i == string::npos)									// When the end of the currency is not found
		{
			throw runtime_error("Please type '/' between currency and weight");
		}
		str = price_tag.substr(0, i);							// The string for the currency
		strip_and_to_lower(str);
		currency = Currency(str);
		if (!currency.is_valid())
		{
			throw runtime_error("Currency \"" + str + "\" is not supported");
		}
		price_tag = price_tag.substr(i + 1);					// Skip the currency

		// Process weight
		strip_and_to_lower(price_tag);
		i = price_tag.find_first_not_of("0123456789.-");		// Find the end of the weight
		if (i == string::npos)									// When the end of the weight is not found
		{
			throw runtime_error("Please enter a valid unit after the weight");
		}
		str = price_tag.substr(0, i);							// The string for the weight
		if (str.empty())										// When the weight is omitted by user
		{
			weight = 1;											// Default to 1
		}
		else
		{
			try
			{
				weight = stod(str);								// Convert the string for the weight to double
				if (weight <= 0)								// When the weight entered is not a positive number
				{
					throw exception();
				}
			}
			catch (exception)
			{
				throw runtime_error("Please enter a valid positive number as weight");
			}
		}
		price_tag = price_tag.substr(i);						// Skip the weight

		// Process unit
		strip_and_to_lower(price_tag);
		unit = Unit(price_tag);
		if (!unit.is_valid())
		{
			throw runtime_error("Unit \"" + price_tag + "\" is not supported");
		}

		this->unit_price = unit_price;
	}

	Product::Product(const string& name, string price_tag) : Product(name, price_tag, 0) { calc_unit_price(); }

	void Product::set_name(const string& name) { this->name = name; }

	void Product::set_price(double price) { this->price = price; }

	void Product::set_currency(const string& currency) { this->currency = Currency(currency); }

	void Product::set_weight(double weight) { this->weight = weight; }

	void Product::set_unit(const string& unit) { this->unit = Unit(unit); }

	double Product::calc_unit_price(const string& unit, const string& currency) const
	{
		double unit_conversion_rate = this->unit.get_conversion_rate(unit);
		
		double currency_conversion_rate = this->currency.get_conversion_rate(currency);

		return price * currency_conversion_rate / weight / unit_conversion_rate;
	}

	double Product::calc_unit_price() { return unit_price = calc_unit_price("lb", "usd"); }

	string Product::get_name() const { return name; }

	double Product::get_price() const { return price; }

	string Product::get_currency() const { return currency.get_name(); }

	double Product::get_weight() const { return weight; }

	string Product::get_unit() const { return unit.get_name(); }

	double Product::get_unit_price() const { return unit_price; }

	string Product::get_price_tag() const {
		//return to_string(price) + currency.get_name() + "/" + to_string(weight) + unit.get_name();
		ostringstream s;
		s << price << currency.get_name() << "/" << weight << unit.get_name();
		return s.str();
	}

	string Product::print_csv() const
	{
		//return name + "\t" + get_price_tag() + "\t" + to_string(unit_price);
		ostringstream s;
		s << name << "\t" << get_price_tag() << "\t" << unit_price;
		return s.str();
	}
}