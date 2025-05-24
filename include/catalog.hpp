#pragma once

#include <map>		// For multimap
#include <string>	// For string

#include "product.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	class Catalog
	{
	private:
		string name;

		multimap<double, Product> catalog;

	public:
		Catalog();

		Catalog(const string& name);

		Catalog(const string& name, const string& file);

		void set_name(const string& name);

		string get_name() const;

		void add_product(const Product& product);

		const Product& get_product(const string& name) const;

		void delete_product(const string& name);

		void load(const string& file);

		void save(const string& file) const;

		void print() const;
	};
}