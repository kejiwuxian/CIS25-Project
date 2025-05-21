#include <memory>
#include <stdexcept>// For runtime_error

#ifdef _WIN32 // Windows MSVC
#include <windows.h>// For _popen, _pclose
#define popen _popen
#define pclose _pclose
#else // Linux, MacOS
#include <stdio.h>	// For popen, pclose
#endif

#include "curl.hpp"

using namespace std;

namespace UnitPriceCalculator
{
	string CURL::fetch(const string& url)
	{
		shared_ptr<char> buf(new char[1024]);	// Dynamically allocate memory and use it as a buffer of char type

		if (!buf)
		{
			throw runtime_error("Error: Failed to allocate memory, please make sure your system have enough aviliable RAM");
		}

		string cmd = "curl -s \"" + url + "\"";
		FILE* pipe = popen(cmd.c_str(), "r");	// Execute curl to fetch data from the API

		if (!pipe)
		{
			throw runtime_error("Error: Failed to execute curl command, please make sure curl is installed and added to PATH");
		}

		string res;
		while (fgets(buf.get(), 1024, pipe) != nullptr)	// Read the output of curl until it is empty
		{
			res += buf.get();
		}

		pclose(pipe);

		if (res.length() == 0)
		{
			throw runtime_error("Error: Failed to fetch \"" + url + "\"");
		}

		return res;
	}
}