//Evan Gordon

#ifndef PARSER_H
#define PARSER_H
#define _CRT_SECURE_NO_WARNINGS //this is to eliminate ms warnings related to stringcpy

#include <string> 
#include <sstream>
#include <vector>
#include <cctype>

//Naeva 1.0
//This class takes the string it is given, and turns it into a vector of strings. 
class Parser
{
public:
	Parser();

	bool recieveMessage(const std::string& word);
	std::string toLowerCase(std::string string);

	~Parser();

	std::vector<std::string> playerInput;
};

#endif 