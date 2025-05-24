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

	int Unit::operator=(int value)
	{
		return this->value = static_cast<values>(value);
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

	double Unit::get_conversion_rate(int from, int to)
	{
		if (!(is_valid(from) && is_valid(to)))
		{
			throw runtime_error("Error: Invalid unit");
		}

		return conversion_rates[from][to];
	}

	double Unit::get_conversion_rate(const string& from, const string& to)
	{
		Unit f = Unit(from);
		Unit t = Unit(to);

		if (!(f.is_valid() && t.is_valid()))
		{
			throw runtime_error("Error: Invalid unit");
		}

		return conversion_rates[f.get_value()][t.get_value()];
	}

	int Unit::get_value() const { return value; }

	bool Unit::is_valid() const { return is_valid(value); }

	string Unit::get_name() const { return get_name(value); }

	string Unit::get_description() const { return get_description(value); }

	double Unit::get_conversion_rate(int to) const { return get_conversion_rate(value, to); }

	double Unit::get_conversion_rate(const string& to) const { return get_conversion_rate(names[value], to); }
}