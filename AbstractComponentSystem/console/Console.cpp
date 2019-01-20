//Evan Gordon

#include "Console.h"

Console::Console() :
	files(), consoleEnabled(true), responsesEnabled(false)
{
	commandNode = files.console.child("commands");
	replyNode = files.consoleReply.child("responses");
}

CommandResult Console::recieveMessage(std::vector<std::string> playerInput)
{
	if (consoleEnabled)
	{
		if (responsesEnabled)//console with AI responses
		{
			return consoleCommand(playerInput);
			//plug into response
			//std::vector<std::string> temp;
			//temp.push_back("spell");			lol what does this even do!?
			//temp.push_back(playerInput[2]);
			//responseGenerator(temp);
		}
		else//case for only console
		{
			return consoleCommand(playerInput);
		}
	}
	else if (responsesEnabled)//this is a case for possible npc's w no console access. move to other class later?
	{
		//responseGenerator(playerInput);
		return UndefCaseInConsole;
	}
	return UndefCaseInConsole;
}

CommandResult Console::consoleCommand(std::vector<std::string> &playerInput)//returns whether it was a successful command entry?
{
	//todo add in code for command rerouting
	bool found = false, commandCalled = false;
	for (pugi::xml_node curr = commandNode.first_child(); curr; curr = curr.next_sibling())//search for correct matching command
	{

		if (playerInput[0] == curr.name())
		{
			found = true;
			for (curr = curr.first_child(); curr; curr = curr.next_sibling())
			{
				if ((playerInput.size() - 1) == curr.text().as_int())//find matching # of arguments for command ( size - 1 to account for spell name)
				{
					//iterate over types of arguments, to ensure argument is correct type
					const int argNum = playerInput.size() - 1;
					int argsChecked = 1;
					Arguments arg;
					if (curr.child("strings") != NULL)
					{
						curr = curr.child("strings");
						for (int i = 0; i < curr.text().as_int(); i++)
						{
							arg.strings.push_back(playerInput[argsChecked]);
							argsChecked++;
						}
						curr = curr.parent();
					}
					if (curr.child("ints") != NULL)
					{
						curr = curr.child("ints");
						for (int i = 0; i < curr.text().as_int(); i++)
						{
							if (isInt(playerInput[argsChecked]))
							{
								arg.ints.push_back(toInt(playerInput[argsChecked]));
								argsChecked++;
							}
							else
							{return IncArguments;}
						}
						curr = curr.parent();
					}
					if (curr.child("floats") != NULL)//&& is float
					{
						curr = curr.child("floats");
						for (int i = 0; i < curr.text().as_int(); i++)
						{
							//push float into arg
							arg.floats.push_back(std::stof( playerInput[argsChecked]));
							argsChecked++;
						}
						curr = curr.parent();
					}
					//commandQueue.push_front(std::pair<std::string, Arguments>(playerInput[0], arg));//successful command
					auto temp = console_commands.find(playerInput[0]);
					if (temp != console_commands.end())
					{
						console_commands[playerInput[0]](arg);//command found, call
						commandCalled = true;
						return Success;
					}
					else
					{
						arg.strings.push_back(playerInput[0]);
						console_commands["invalidcommand"](arg);
						return IncArguments;
					}
					commandCalled = true;
					curr = curr.parent();
					return Success;
				}
			}
			curr = curr.parent();
		}
	}
	//if(!found){return incCommand;}
	//if(!commandCalled){return incArguments;}
	return CommandResult::IncCommand;
}

bool Console::isCommandWord(std::string word)
{
	//todo add in reroute commands
	for (pugi::xml_node curr = commandNode.first_child(); curr; curr = curr.next_sibling())//search for correct matching command
	{
		if (word == curr.name())
		{return true;}
	}
	return false;
}

void Console::setDefaultCommand(Command cmd)
{
	for (pugi::xml_node curr = commandNode.first_child(); curr; curr = curr.next_sibling())//set default command for all commands
	{console_commands.insert(std::pair<std::string, Command>(curr.name(), cmd));}
}

void Console::setCommand(const std::string& name, Command newCommand)
{
	auto temp = console_commands.find(name);
	if (temp != console_commands.end())
	{temp->second = newCommand;}
	else
	{console_commands["invalidcommand"](Arguments());}
	
}

std::pair<std::string, Arguments> Console::getCommand()
{
	if (commandQueue.size() > 0)
	{
		auto last = commandQueue[commandQueue.size() - 1];
		commandQueue.pop_back();
		return last;
	}
	else
	{return std::pair<std::string, Arguments>();}
}

int Console::getHasCommand()
{return commandQueue.size();}

//creates and returns a vector of names of the different commands in the stack, in the order in which they-
//will be called when retrieved from console.
std::vector<std::string> Console::getCommandNames()
{
	std::vector<std::string> result;
	for (int i = commandQueue.size() - 1; i >= 0; i--)
	{result.push_back(commandQueue[i].first);}
	return result;
}

std::string Console::responseGenerator(std::vector<std::string> &playerInput)
{return "";}

Console::~Console() {}