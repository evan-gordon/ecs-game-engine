//Evan Gordon

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "IsState.h"
#include "../systems/SystemManager.h"
#include "../g_Functions.h"

class GameState : public IsState
{
private:
	bool paused;
	SystemManager manager;

public:
	GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, const bool& isGame);
	~GameState();

	void initialize();
	StateType update();
	void draw();
	bool handleEvents();

	SystemManager& getManager();
};

#endif