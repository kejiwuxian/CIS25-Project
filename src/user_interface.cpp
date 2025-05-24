#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <filesystem>
namespace fs = std::filesystem;

#include "user_interface.hpp"
#include "catalog.hpp"
#include "util.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	int UI::run(int argc, char** argv)
	{
		argc > 1 ? handle_arguments(argc, argv) : handle_interactions();
		return 0;
	}

	void UI::print_supported_currencies()
	{
		if (Currency::currencies.empty())
		{
			Currency::init();
		}

		cout << "Supported currencies:" << endl;
		int i = 0;
		for (auto it = Currency::currencies.begin();it != Currency::currencies.end();it++)
		{
			cout << left << setw(8) << it->first;
			if (++i % 15 == 0)
			{
				cout << endl;
			}
		}
		cout << endl << endl;
	}

	void UI::print_supported_units()
	{
		cout << "Supported units:" << endl;
		for (int i = 0;i < Unit::invalid;i++)
		{
			cout << '\t' << left << setw(8) << Unit::names[i] << Unit::descriptions[i] << endl;
		}
		cout << endl;
	}

	void UI::print_help()
	{
		cout << "Calculate the unit price in different units and currencies." << endl << endl;
		cout << "Usage:" << endl;
		cout << "    unitprice [price]original_currency/[weight]original_unit target_currency/target_unit" << endl;
		cout << endl;
		cout << left << setw(40) << "    price" << "Optional original price in original_currency, needs to be a positive number" << endl;
		cout << left << setw(40) << "    original_currency" << "The original currency of [price], needs to be one of supported_currencies" << endl;
		cout << left << setw(40) << "    weight" << "Optional original weight in original_unit, needs to be a positive number" << endl;
		cout << left << setw(40) << "    original_unit" << "The original unit of [weight], needs to be one of supported_units" << endl;
		cout << left << setw(40) << "    target_currency" << "The target currency of the unit price, needs to be one of supported_currencies" << endl;
		cout << left << setw(40) << "    target_unit" << "The target unit of the unit price, needs to be one of supported_units" << endl;
		cout << endl;
		cout << "Examples:" << endl;
		cout << left << setw(40) << "    unitprice 4.99USD/1LB EUR/KG" << "How much euros per kilogram of a product that costs $4.99 per pound is worth" << endl;
		cout << left << setw(40) << "    unitprice 1usd/2.5oz eur/g" << "How much euros per gram of a product that costs $1 per 2.5 ounces is worth" << endl;
		cout << left << setw(40) << "    unitprice uSd/JiN eUr/kG" << "How much euros per kilogram of a product that costs $1 per pound is worth" << endl;
		cout << endl;
		print_supported_currencies();
		print_supported_units();
	}

	void UI::handle_arguments(int argc, char** argv)
	{
		// An example use of switch statement
		if (argc == 3)
		{
			Product product("", string(argv[1]));
			string target = string(argv[2]);
			int i = target.find('/');
			if (i == string::npos)
			{
				throw runtime_error("Please type '/' between currency and unit");
			}
			string currency = target.substr(0, i);
			string unit = target.substr(i + 1);
			cout << left << setw(16) << setprecision(14) << product.calc_unit_price(currency, unit) << currency << " per " << unit << endl << endl;
		}
		// Unexpected number of arguments
		else
		{
			print_help();
		}
	}

	void UI::handle_interactions()
	{
		string str;
		cout << "Please enter the catalog name: ";
		getline(cin, str);
		Catalog catalog(str);
		if (fs::exists(fs::path(str + ".csv")))
		{
			catalog.load(str + ".csv");
		}

		while (true)
		{
			Util::clear_console();
			catalog.print();
			cout << "(add [name], del [name], save, exit)" << endl;
			cout << "> ";
			getline(cin, str);
			string cmd = str.substr(0, 4);
			string name = str.substr(4);
			if (cmd == "add ")
			{
				cout << "Please enter the price tag: ";
				getline(cin, str);
				try
				{
					catalog.add_product(Product(name, str));
				}
				catch (exception& e)
				{
					cout << e.what() << endl;
					cout << "Please press any key to retry..." << endl;
					Util::getch();
				}

			}
			else if (cmd == "del ")
			{
				catalog.delete_product(name);
			}
			else if (cmd == "save")
			{
				catalog.save(catalog.get_name() + ".csv");
			}
			else if (cmd == "exit")
			{
				return;
			}
			else
			{
				cout << "Invalid command, please press any key to retry..." << endl;
				Util::getch();
			}
		}
	}
}