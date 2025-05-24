#pragma once

using namespace std;

namespace UnitPriceCalculator
{
	class UI
	{
	public:
		static int run(int argc, char** argv);

		static void print_supported_currencies();

		static void print_supported_units();

		static void print_help();

		static void handle_arguments(int argc, char** argv);

		static void handle_interactions();
	};
}