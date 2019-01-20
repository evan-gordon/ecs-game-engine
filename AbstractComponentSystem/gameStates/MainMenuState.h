//Evan Gordon

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <exception>

#include "IsState.h"
#include "../ui/ui_Button.h"
#include "../g_Functions.h"
#include "../services/Locator.h"

class MainMenuState: public IsState
{
private:
	ui_Button mapMaker, playGame, settings;
	sf::Texture background, menuButton, menuButtonPressed, settingsIconText;
	sf::Sprite mainMenuBackground;
	sf::Vector2i localPosition;
	bool clicked, countDown;
	sf::Clock gameTime;
	sf::Time deltaTime;

public:
	MainMenuState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont);
	~MainMenuState();
	void initialize();
	StateType update();
	void draw();
	bool handleEvents();
};

#endif
