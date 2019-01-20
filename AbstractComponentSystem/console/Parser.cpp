//Evan Gordon

#include "Parser.h"

Parser::Parser() :
	playerInput()
{
}

//edit this function so that it can somehow return a response that says if hte entered word is a keywords, so keywords can recieve a different colored text
bool Parser::recieveMessage(const std::string& word)//returns bool false if no text in word
{
	if (word.size() != 0)
	{
		std::string input = toLowerCase(word);
		playerInput.push_back(input);
		return true;
	}
	return false;
}

std::string Parser::toLowerCase(std::string string)
{
	std::vector<char> chars(string.begin(), string.end());
	std::string result("");
	for (size_t i = 0; i < string.size(); i++)
	{
		result += std::tolower(chars[i]);
	}
	return result;
}

Parser::~Parser() {}