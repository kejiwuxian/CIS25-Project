#pragma once

#include <string>	// For string

#include "unit.hpp"
#include "currency.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	class Product
	{
	private:
		string name;
		
		double weight;
		
		Unit unit;
		
		double price;
		
		Currency currency;

		double unit_price;

	public:
		Product();

		Product(const string& name, double price, const string& currency, double weight, const string& unit, double unit_price);

		Product(const string& name, double price, const string& currency, double weight, const string& unit);

		Product(const string& name, string price_tag, double unit_price);

		Product(const string& name, string price_tag);

		void set_name(const string& name);

		void set_price(double price);

		void set_currency(const string& currency);

		void set_weight(double weight);

		void set_unit(const string& unit);

		double calc_unit_price(const string& unit, const string& currency) const;

		double calc_unit_price();

		string get_name() const;

		double get_price() const;

		string get_currency() const;

		double get_weight() const;
		
		string get_unit() const;

		double get_unit_price() const;

		string get_price_tag() const;

		string print_csv() const;
	};
}