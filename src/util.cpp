#include <cctype>	// For tolower

#ifdef _WIN32 // Windows MSVC
#include <conio.h>	// For _getch
#include <windows.h>// For _popen, _pclose
#define popen _popen
#define pclose _pclose
#else // Linux, MacOS
#include <termios.h>// For termios, tcgetattr
#include <unistd.h>	// For STDIN_FILENO
#include <stdio.h>	// For popen, pclose
#endif

#include "util.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	// Removes leading, and trailing whitespaces, \r and \n then convert to lowercase
	void Util::strip_and_to_lower(string& str)
	{
		// Strip Left
		while (!str.empty() && string(" \r\n").find(str[0]) != string::npos)
		{
			str.erase(0, 1);
		}

		// Strip Right
		while (!str.empty() && string(" \r\n").find(str[str.length() - 1]) != string::npos)
		{
			str.pop_back();
		}

		// To Lower
		for (size_t i = 0;i < str.length();i++)
		{
			str[i] = tolower(str[i]);
		}
	}

#ifdef _WIN32 // Windows MSVC
	char Util::getch()
	{
		return static_cast<char>(_getch());
	}

	void Util::clear_console()
	{
		system("cls");
	}
#else // Linux, MacOS
	char Util::getch()
	{
		struct termios oldt, newt;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		char ch = static_cast<char>(getchar());
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		return ch;
	}

	void Util::clear_console()
	{
		system("clear");
	}
#endif
}