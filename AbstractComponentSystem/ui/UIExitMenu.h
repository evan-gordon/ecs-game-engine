//Evan Gordon

#ifndef UIEXITMENU_H
#define UIEXITMENU_H

#include <SFML/Graphics.hpp>

#include<memory>

#include "UI.h"

class UIExitMenu:public UI
{
private:

public:
	bool exit, cancelSelected;
	sf::Text saveExit, cancel;
	sf::Sprite selectorLeft, selectorRight;

	UIExitMenu();
	UIExitMenu(std::shared_ptr<sf::Font> font, sf::Texture& texture, sf::Vector2f position);
	~UIExitMenu ();

	void update();
	void moveSelector();
	bool toggle();
	void draw(sf::RenderWindow& window);
};

#endif