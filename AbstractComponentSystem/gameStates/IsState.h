//Evan Gordon

#ifndef ISSTATE_H
#define ISSTATE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

#include "../g_Functions.h"

class IsState
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Event> gameEvent;
	std::shared_ptr<sf::Font> gameFont;
public:
	IsState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont);
	virtual ~IsState();

	virtual void initialize() = 0;
	virtual StateType update() = 0;
	virtual void draw() = 0;
	virtual bool handleEvents() = 0;

};

#endif