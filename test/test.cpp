#include "gtest/gtest.h"

#include "curl.hpp"

TEST(CURL, fetch)
{
	EXPECT_EQ(UnitPriceCalculator::CURL::fetch("https://lonedark.com/").length(), 1416);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}