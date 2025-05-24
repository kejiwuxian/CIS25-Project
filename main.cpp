#include <iostream>

#include "user_interface.hpp"

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		return UnitPriceCalculator::UI().run(argc, argv);
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
}