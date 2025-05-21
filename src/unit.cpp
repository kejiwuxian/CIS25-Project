#include <stdexcept>// For runtime_error

#include "unit.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	Unit::Unit() : value{ invalid } {}

	Unit::Unit(int value) : value{ static_cast<values>(value) } {}

	Unit::Unit(const string& unit) : Unit()
	{
		for (int i = 0;i < invalid;i++)
		{
			if (names[i] == unit)
			{
				value = static_cast<values>(i);
				return;
			}
		}
	}

	bool Unit::is_valid(int value)
	{
		return value >= 0 && value < invalid;
	}

	string Unit::get_name(int value)
	{
		if (!is_valid(value))
		{
			throw runtime_error("Error: Invalid unit");
		}

		return names[value];
	}

	string Unit::get_description(int value)
	{
		if (!is_valid(value))
		{
			throw runtime_error("Error: Invalid unit");
		}

		return descriptions[value];
	}

	int Unit::get_value() const { return value; }

	bool Unit::is_valid() const { return Unit::is_valid(value); }

	string Unit::get_name() const { return Unit::get_name(value); }

	string Unit::get_description() const { return Unit::get_description(value); }

	int Unit::operator=(int value) { return this->value = static_cast<values>(value); }
}