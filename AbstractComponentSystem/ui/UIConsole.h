//Evan Gordon

#ifndef UICONSOLE_H
#define UICONSOLE_H

#include <SFML/Graphics.hpp>

#include <deque>
#include <memory>

#include "UI.h"
#include "../console/CManager.h"

enum ConsoleState{LOG, CONSOLE, CLOSED};

class UIConsole : public UI
{
public:
	sf::Text currInput, space, consoleText;
	std::vector<sf::Text> currSentence;//used for drawing purposes
	std::shared_ptr<sf::Font> gameFont;
	std::shared_ptr<CManager> consoleManager;

	UIConsole(std::shared_ptr<CManager> con);//used for base initilization before init() in serviceLocator
	UIConsole(std::shared_ptr<sf::Font> gameFont, sf::RenderWindow& window, std::shared_ptr<CManager> console);

	void readInput(sf::Event);
	void sendWord();
	void deleteChar();
	void update();
	void sendMessage();
	void readEventLog();
	bool toggle();
	bool getCanDraw();
	void handleEvents(std::shared_ptr<sf::Event> event);
	const ConsoleState& getState();
	void draw(sf::RenderWindow& window);
	std::string trim(std::string& string);//for string trimming
										  //possibly add a find last command function that will search for the last command that is oriented to the right in the log
	void orientRight(std::vector<sf::Text>& vec, int xOffset, int yPos);
	void moveUp();
	int getInputWidth();

	~UIConsole();

private:
	std::deque<std::vector<sf::Text>> consoleLog;//this is a deque of vectors so that each word can be stored as its own sf::Text object, so command words
												 //can be displayed in a different color
	ConsoleState state;
	float windowCenter;
	int orientDist, UILowerBounds, lSpace;//not sure about this 550 dist, its temporary for now
	/*This class is intended to act as a Dev console for the game. The console will more than likely only be accesable during access of the map maker, but for now its
	open to both. The console will log all important data logs, such as player postion, or spawning of world objects. A scroll function will need to be added so this menu's
	information can be scrolled through. Also later on it might be useful to add a functionality so that this class can output a log file for errors and the like.*/
};

#endif