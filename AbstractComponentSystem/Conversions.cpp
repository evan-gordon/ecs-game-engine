//Evan Gordon

#include "Conversions.h"

bool isInt(std::string string)
{
	std::string::iterator it = string.begin();
	if(*it == '-')
	{
		it++;
	}
	while(it != string.end() && std::isdigit(*it))
	{
		it++;
	}
	return (!string.empty() && it == string.end());
}

int toInt(std::string& string)
{
	return atoi(string.c_str());
}