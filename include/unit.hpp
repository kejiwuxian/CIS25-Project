#pragma once

#include <string>	// For string

using namespace std;

namespace UnitPriceCalculator
{
	class Unit
	{
	public:
		// Enum for the units, an example use of static_cast
		enum values
		{
			oz = 0,
			lb,
			kg,
			jin,
			g,
			invalid
		};

		// A list of names for the units, an example use of array
		inline static const string names[] = { "oz","lb","kg","jin","g" };

		// A list of descriptions for the units, an example use of array
		inline static const string descriptions[] =
		{
			"Ounce (US weight unit)",		// oz
			"Pound (US weight unit)",		// lb
			"Kilogram (metric weight unit)",// kg
			"Jin (Chinese weight unit)",	// jin
			"Gram (metric weight unit)"		// g
		};

	private:
		values value;

	public:
		Unit();

		Unit(int value);

		Unit(const string& unit);

		static bool is_valid(int value);

		static string get_name(int value);

		static string get_description(int value);

		int get_value() const;

		bool is_valid() const;

		string get_name() const;

		string get_description() const;

		int operator=(int value);
	};
}