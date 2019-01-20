//Evan Gordon

#include "GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, const bool& isGame) :IsState(window, gameEvent, gameFont),
paused(false), manager(window, gameEvent, gameFont, isGame)//shared ptrs?
{}

void GameState::initialize()
{
	window->setMouseCursorVisible(false);
}

StateType GameState::update()
{
	return manager.update();
}

void GameState::draw()
{
	manager.draw();
}

bool GameState::handleEvents()
{
	manager.handleEvents();
	return false;
}

SystemManager& GameState::getManager()
{
	return manager;
}

GameState::~GameState() {}