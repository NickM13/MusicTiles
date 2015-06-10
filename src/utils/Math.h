#pragma once
#include <string>
#include <sstream>

namespace Math {
	template<class T>
	static std::string numToString(T n)
	{
		std::string save = "";
		std::ostringstream convert;
		convert.str(std::string());
		try {
			convert << n;
			save = convert.str();
			return save;
		}
		catch (std::exception e) {
			return std::string("Incorrect Variable Type!");
		}
	}

	static std::string subchar(char* chararray, int start, int end)
	{
		std::string subbed;
		for (int i = start; i < end + 1; i++)
		{
			subbed += chararray[i];
		}
		return subbed;
	}
};
