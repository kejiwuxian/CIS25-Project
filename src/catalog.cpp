#include <stdexcept>	// For runtime_error
#include <fstream>		// For ifstream, ofstream
#include <string>		// For getline

#include "catalog.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	Catalog::Catalog() : name{ "" }, catalog{ multimap<double, Product>() } {}

	Catalog::Catalog(const string& name) : Catalog() { this->name = name; }

	Catalog::Catalog(const string& name, const string& file) : Catalog(name) { load(file); }

	void Catalog::set_name(const string& name) { this->name = name; }

	string Catalog::get_name() const { return name; }

	void Catalog::add_product(const Product& product) { catalog.insert({ product.get_unit_price(), product }); }

	const Product& Catalog::get_product(const string& name) const
	{
		for (auto it = catalog.begin();it != catalog.end();it++)
		{
			if (it->second.get_name() == name)
			{
				return it->second;
			}
		}

		throw runtime_error("Product " + name + " not found");
	}

	void Catalog::delete_product(const string& name)
	{
		for (auto it = catalog.begin();it != catalog.end();it++)
		{
			if (it->second.get_name() == name)
			{
				catalog.erase(it);
				return;
			}
		}

		throw runtime_error("Product " + name + " not found");
	}

	void Catalog::load(const string& file)
	{
		ifstream s(file);

		if (!s.is_open())
		{
			throw runtime_error("Failed to load " + file);
		}

		string str, name, price_tag;
		getline(s, str);
		while (!s.eof())
		{
			getline(s, name, '\t');
			if (name.empty())
			{
				continue;
			}
			getline(s, price_tag, '\t');
			getline(s, str);
			Product product(name, price_tag, stoi(str));
			add_product(product);
		}

		s.close();
	}

	void Catalog::save(const string& file) const
	{
		ofstream s(file);

		if (!s.is_open())
		{
			throw runtime_error("Failed to open " + file);
		}

		s << "name\tprice_tag\tunit_price" << endl;
		for (auto it = catalog.begin();it != catalog.end();it++)
		{
			s << it->second.print_csv() << endl;
		}

		s.close();
	}
}