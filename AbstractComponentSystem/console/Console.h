//Evan Gordon

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../pugixml.hpp"

#include <vector>
#include <deque>
#include <string>
#include <functional>
#include <map>

#include "Files.h"
#include "../Conversions.h"
#include "Arguments.h"
//#include "../services/Locator.h"

typedef std::function<void(const Arguments&)> Command;

enum CommandResult { Success, IncArguments, IncCommand, UndefCaseInConsole };

class Console
{
public:
	Console();
	~Console();

	CommandResult recieveMessage(std::vector<std::string> playerInput);
	CommandResult consoleCommand(std::vector<std::string> &playerInput);
	bool isCommandWord(std::string);
	std::string responseGenerator(std::vector<std::string> &playerInput);

	int getHasCommand();
	std::pair<std::string, Arguments> getCommand();
	void setDefaultCommand(Command cmd);
	void setCommand(const std::string& name, Command newCommand);
	std::vector<std::string> getCommandNames();//use this to push all waiting commands into the message broadcast in sysmanager

private:
	bool consoleEnabled, responsesEnabled;
	std::map<std::string, Command> console_commands;

	std::deque<std::pair<std::string, Arguments>> commandQueue;
	Files files;
	pugi::xml_node commandNode, replyNode;
};

#endif