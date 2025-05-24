#include "gtest/gtest.h"

#include "curl.hpp"
#include "unit.hpp"
#include "currency.hpp"
#include "product.hpp"
#include "catalog.hpp"

using namespace UnitPriceCalculator;

TEST(CURL, fetch)
{
	EXPECT_EQ(CURL::fetch("https://lonedark.com/").length(), 1416);
}

TEST(Unit, Unit)
{
	for (int i = 0;i < Unit::invalid;i++)
	{
		EXPECT_TRUE(Unit(Unit::names[i]).is_valid());
	}
	EXPECT_FALSE(Unit("Unit").is_valid());
}

TEST(Unit, is_valid)
{
	for (int i = 0;i < Unit::invalid;i++)
	{
		EXPECT_TRUE(Unit(i).is_valid());
	}
	EXPECT_FALSE(Unit(Unit::invalid).is_valid());
}

TEST(Unit, get_name)
{
	for (int i = 0;i < Unit::invalid;i++)
	{
		EXPECT_EQ(Unit(i).get_name(), Unit::names[i]);
	}
	EXPECT_THROW(Unit(Unit::invalid).get_name(), runtime_error);
}

TEST(Unit, get_description)
{
	for (int i = 0;i < Unit::invalid;i++)
	{
		EXPECT_EQ(Unit(i).get_description(), Unit::descriptions[i]);
	}
	EXPECT_THROW(Unit(Unit::invalid).get_description(), runtime_error);
}

TEST(Unit, get_conversion_rate)
{
	for (int i = 0;i < Unit::invalid;i++)
	{
		Unit unit(i);
		for (int j = 0;j < Unit::invalid;j++)
		{
			EXPECT_EQ(unit.get_conversion_rate(j), Unit::conversion_rates[i][j]);
		}
	}
	EXPECT_THROW(Unit::get_conversion_rate(0, Unit::invalid), runtime_error);
	EXPECT_THROW(Unit::get_conversion_rate(Unit::invalid, 0), runtime_error);
}

TEST(Currency, is_valid)
{
	EXPECT_TRUE(Currency("usd").is_valid());
	EXPECT_FALSE(Currency().is_valid());
}

TEST(Currency, get_description)
{
	EXPECT_TRUE(Currency("usd").get_description().length() > 0);
	EXPECT_THROW(Currency().get_description(), runtime_error);
}

TEST(Currency, get_conversion_rate)
{
	EXPECT_TRUE(Currency("usd").get_conversion_rate("cny") > 0);
	EXPECT_THROW(Currency().get_conversion_rate("cny"), runtime_error);
}

TEST(Product, print_csv)
{
	EXPECT_EQ(Product("A", "usd/lb").print_csv(), "A\t1usd/1lb\t1");
}

TEST(Catalog, save_load)
{
	Catalog catalog("A");
	catalog.add_product(Product("A", "usd/lb"));
	catalog.save("catalog.csv");
	catalog = Catalog("B", "catalog.csv");
	EXPECT_EQ(catalog.get_product("A").print_csv(), "A\t1usd/1lb\t1");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}