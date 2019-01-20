//Evan Gordon

#include "CManager.h"

CManager::CManager() {}

//used for pushing commands in the console UI
void CManager::sendMessage()
{
	if (parser.playerInput.size() == 0 || (parser.playerInput.size() == 1 && parser.playerInput[0] == " "))
	{
		parser.playerInput.clear(); 
		return;
	}

	CommandResult result = console.recieveMessage(parser.playerInput);//generate response at some point?
	if (result == IncArguments) { logger.push("Invalid Arguments Error: see help function for details"); }
	else if (result == IncCommand) { logger.push("Invalid Command Name Error: see help function for details"); }
	parser.playerInput.clear();
}

void CManager::invalidCommand(const Arguments& arg)
{
	if (arg.strings.size() != 0)
	{
		logger.push("Unable to call command " + arg.strings[arg.strings.size() - 1] + " arguments input are: str " +
			std::to_string(arg.strings.size()) + ", int: " + std::to_string(arg.ints.size()) + ", float: " + std::to_string(arg.floats.size()) + ".");//command not found
	}
	else
	{
		logger.push("Unable to call command arguments input are: str " +
			std::to_string(arg.strings.size()) + ", int: " + std::to_string(arg.ints.size()) + ", float: " + std::to_string(arg.floats.size()) + ".");//command not found
	}
}

int CManager::getHasCommand(){return console.getHasCommand();}

void CManager::log(const std::string& s)
{
	if (s.size() == 0){ return; }
	logger.push(s);
}

void CManager::logErr()
{
	std::ostringstream oStream;
	std::string str;
	sf::err().rdbuf(oStream.rdbuf());
	str = oStream.str();
	log(str);
}

std::vector<std::string> CManager::readLog()
{
	return logger.read();
}

//this command acts as an interface to the Console class
//accepts vector of strings that act as all console arguments
//returns false if command was not called
bool CManager::callCommand(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		return false;
	}
	for (auto it = args.begin(); it != args.end(); it++)
	{
		parser.recieveMessage(*it);
	}

	CommandResult result = console.recieveMessage(parser.playerInput);
	parser.playerInput.clear();
	if (result == Success) { return true; }
	else if (result == IncArguments) { logger.push("Invalid Arguments Error: see help function for details"); }
	else if (result == IncCommand) { logger.push("Invalid Command Name Error: see help function for details"); }
	return false;
}
CManager::~CManager() {}