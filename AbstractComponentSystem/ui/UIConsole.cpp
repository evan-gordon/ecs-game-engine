//Evan Gordon

#include "UIConsole.h"

UIConsole::UIConsole(std::shared_ptr<CManager> con) : consoleManager(con), orientDist(350), UILowerBounds(55), lSpace(25){}

UIConsole::UIConsole(std::shared_ptr<sf::Font> gameFont, sf::RenderWindow& window, std::shared_ptr<CManager> console) :
	orientDist(350),  lSpace(25), currInput("", *gameFont, 14), consoleManager(console), gameFont(gameFont), space(" ", *gameFont, 14), state(CLOSED), consoleText("Closed", *gameFont, 14)
{
	UILowerBounds = window.getSize().y - 55;
	windowCenter = window.getSize().x / 2.0f;
	currInput.setPosition(windowCenter + orientDist, (float)UILowerBounds);
}

const ConsoleState& UIConsole::getState(){return state;}

void UIConsole::handleEvents(std::shared_ptr<sf::Event> event)
{
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Tilde)
	{
		toggle();
	}
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::BackSpace)
	{
		deleteChar();
	}
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Space)
	{
		sendWord();
	}
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Return)
	{
		update();
		sendMessage();
	}
	if (event->type == sf::Event::TextEntered && ((event->text.unicode > 0x02B && event->text.unicode < 0x03C) ||
		(event->text.unicode > 0x05A && event->text.unicode < 0x05E) || event->text.unicode == 0x027 || event->text.unicode == 0x03D ||
		(event->text.unicode > 0x060 && event->text.unicode < 0x07B)))
	{
		readInput(*event);//log this input in current input
	}
}

void UIConsole::update()
{
	if (currInput.getString() != "") 
	{ sendWord(); }

	if (currSentence.size() != 0)//push command
	{
		consoleLog.push_front(currSentence);
		if (consoleLog.size() > 50){consoleLog.resize(50);}

		currInput.setString("");
		moveUp();
		currSentence.clear();
	}
}

void UIConsole::sendMessage(){consoleManager->sendMessage();}

void UIConsole::readInput(sf::Event event)
{
	if (getInputWidth() <= 580)
	{
		int deltaX = (int)currInput.getLocalBounds().width;
		currInput.setString(currInput.getString() + (char)event.key.code);
		char temp = (char)event.key.code;
		currInput.setOrigin(currInput.getLocalBounds().width, 0);
		deltaX = (int)currInput.getLocalBounds().width - deltaX;

		for (auto it = currSentence.begin(); it != currSentence.end(); it++)
		{
			it->setPosition(it->getPosition().x - deltaX, it->getPosition().y);
		}
	}
}

void UIConsole::deleteChar()
{
	if (currInput.getString().getSize() == 0 && currSentence.size() == 0){return;}

	if (currInput.getString().getSize() != 0)
	{
		std::string temp = currInput.getString();
		temp.pop_back();
		currInput.setString(temp);
	}
	else
	{
		currInput.setString(currSentence[currSentence.size() - 1].getString());
		currInput.setFillColor(sf::Color::White);
		currSentence.pop_back();
	}

	//move everything over to account for deletion
	currInput.setOrigin(currInput.getLocalBounds().width, 0);
	orientRight(currSentence, (int)currInput.getLocalBounds().width + (int)space.getLocalBounds().width, UILowerBounds);
}

void UIConsole::sendWord()
{
	std::string temp(currInput.getString());
	bool hasWord = consoleManager->parser.recieveMessage(temp);
	if (hasWord)
	{
		bool isCommand = consoleManager->console.isCommandWord(trim(temp));//check if word is command word
		currSentence.push_back(currInput);
		if (isCommand) { currSentence[currSentence.size() - 1].setFillColor(sf::Color::Yellow); }
		currInput.setString("");
		currInput.setOrigin(0, 0);
		currSentence[currSentence.size() - 1].setOrigin(currSentence[currSentence.size() - 1].getLocalBounds().width, 0);
		orientRight(currSentence, (int)space.getLocalBounds().width, UILowerBounds);//account for space that was just pressed
	}
}

void UIConsole::readEventLog()
{
	auto logs = consoleManager->readLog();
	if (logs.size() != 0)
	{
		std::vector<sf::Text> temp;

		for (int i = 0; i < (int)logs.size(); i++)
		{
			temp.push_back(sf::Text(logs[i], *gameFont, 14));
			temp[0].setPosition(windowCenter - orientDist, (float)UILowerBounds);
			consoleLog.push_front(temp);
			moveUp();
			temp.clear();
		}
	}
}

bool UIConsole::toggle()
{
	if (state == CLOSED)
	{
		state = LOG;
		consoleText.setString("Log");
		return true;
	}
	else if (state == LOG)
	{
		state = CONSOLE;
		consoleText.setString("Console");
		return true;
	}
	else
	{
		state = CLOSED;
		consoleText.setString("Closed");
		return false;
	}
}

bool UIConsole::getCanDraw()
{
	if (state != CLOSED)
	{return true;}
	return false;
}

void UIConsole::draw(sf::RenderWindow& window)
{
	window.draw(currInput);
	for (int i = 0; i < 50; i++)//only draw the first 50? entries
	{
		if (i == consoleLog.size()) { break; }
		for (size_t j = 0; j < consoleLog[i].size(); j++)
		{
			window.draw(consoleLog[i][j]);
		}
	}
	for (size_t i = 0; i < currSentence.size(); i++)
	{
		window.draw(currSentence[i]);
	}

	window.draw(currInput);
	window.draw(consoleText);
}

void UIConsole::orientRight(std::vector<sf::Text>& vec, int xOffset, int yPos)
{
	if (vec.size() != 0 && vec[0].getOrigin().x != 0)
	{
		for (int i = vec.size() - 1; i > -1; i--)
		{
			if (i == vec.size() - 1)
			{vec[i].setPosition(windowCenter + orientDist - xOffset, (float)yPos);}
			else
			{vec[i].setPosition(vec[i + 1].getPosition().x - vec[i + 1].getLocalBounds().width - space.getLocalBounds().width, (float)yPos);}
		}
	}
}

//move all existing text up one line
void UIConsole::moveUp()
{
	for (auto outer_it = consoleLog.begin(); outer_it != consoleLog.end(); outer_it++)
	{
		for (auto inner_it = outer_it->begin(); inner_it != outer_it->end(); inner_it++)
		{
			inner_it->setPosition(inner_it->getPosition().x, (inner_it->getPosition().y - lSpace));
		}//this distance thing might need to go
	}
}

//trim leading and trailing spaces from string
std::string UIConsole::trim(std::string& str)
{
	if (str.size() == 0) { return str; }
	const char* spaces = " \t\n\r\f\v";
	str.erase(0, str.find_first_not_of(spaces));//leading spaces
	str.erase(str.find_last_not_of(spaces) + 1);//trailing spaces
	return str;
}

int UIConsole::getInputWidth()
{
	int result(0);
	for (auto it = currSentence.begin(); it != currSentence.end(); it++)
	{
		result = (int)it->getLocalBounds().width;
	}
	return (int)(result + currInput.getLocalBounds().width);
}

UIConsole::~UIConsole() {}