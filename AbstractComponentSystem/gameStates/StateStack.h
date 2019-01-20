//Evan Gordon

#ifndef STATESTACK_H
#define STATESTACK_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <utility>
#include <exception>

#include "../g_Functions.h"
#include "IsState.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "../systems/SystemManager.h"
#include "MapSelectState.h"
#include "MapCreatorState.h"
#include "SettingsState.h"
#include "../services/Locator.h"

class StateStack
{
private:
	StateType newState;//definition in globals
	sf::Text versionNum;

	std::vector<std::pair<StateType, std::shared_ptr<IsState>>> stack;

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Event> gameEvent;
	std::shared_ptr<sf::Font> gameFont;

public:
	StateStack();
	~StateStack();

	void push();
	void pop();
	bool handleEvents();
	void update();
	void draw();
};

#endif