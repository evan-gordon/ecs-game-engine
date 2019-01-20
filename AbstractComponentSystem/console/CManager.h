//Evan Gordon

#ifndef CMANAGER_H
#define CMANAGER_H

#include <SFML/System.hpp>

#include "Parser.h"
#include "Console.h"
#include "EventLog.h"

#include <string>

//The console manager is here to direct input to a small degree, between the parser and the console
//also is used for manual calling of commands, if nessisary
class CManager
{
public:
	Parser parser;
	Console console;

	CManager();
	void sendMessage();
	void invalidCommand(const Arguments& arg);
	void log(const std::string&);
	void logErr();
	int getHasCommand();//changed to int so that cases could happend (ie if commands are called via code) that multiple commands could pile up
	bool callCommand(std::vector<std::string> args);
	std::vector<std::string> readLog();

	~CManager();

private:
	EventLog logger;
};

#endif