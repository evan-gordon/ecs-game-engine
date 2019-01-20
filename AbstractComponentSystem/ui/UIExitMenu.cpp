//Evan Gordon

#include "UIExitMenu.h"

UIExitMenu::UIExitMenu():
	exit(false), cancelSelected(false)
{}

UIExitMenu::UIExitMenu(std::shared_ptr<sf::Font> font, sf::Texture& texture, sf::Vector2f position) : UI(true, texture),
							exit(false), cancelSelected(false), saveExit("Save and Exit", *font, 14), cancel("Cancel", *font, 14), 
								selectorLeft(texture, sf::IntRect(191, 192, 6, 42)), selectorRight(texture, sf::IntRect(226, 192, 6, 42))
{
	UI::image.setTextureRect(sf::IntRect(148, 0, 288, 192));
	UI::image.setOrigin(144, 71);
	UI::image.setPosition(position);
	saveExit.setOrigin(saveExit.getLocalBounds().width/2, saveExit.getLocalBounds().height/2);
	cancel.setOrigin(cancel.getLocalBounds().width/2, cancel.getLocalBounds().height/2);
	saveExit.setPosition((float)position.x, (float)position.y - 10.0f);
	cancel.setPosition(position.x, position.y + 30.0f);
	selectorLeft.setOrigin(0, 16);
	selectorRight.setOrigin(0, 16);
	moveSelector();
}

void UIExitMenu::update()
{
	if(!cancelSelected)
	{exit = true;}
	else
	{toggle();}
}

void UIExitMenu::moveSelector()
{
	if(!cancelSelected)
	{
		selectorLeft. setPosition(saveExit.getPosition().x - saveExit.getLocalBounds().width/2.0f - 8.0f, saveExit.getPosition().y - 2.0f);
		selectorRight.setPosition(saveExit.getPosition().x + saveExit.getLocalBounds().width/2.0f + 8.0f, saveExit.getPosition().y - 2.0f);
	}
	else
	{
		selectorLeft. setPosition(cancel.getPosition().x - cancel.getLocalBounds().width/2.0f - 8.0f, cancel.getPosition().y - 2.0f);
		selectorRight.setPosition(cancel.getPosition().x + cancel.getLocalBounds().width/2.0f + 8.0f, cancel.getPosition().y - 2.0f);
	}
}

bool UIExitMenu::toggle(){return UI::toggle();}

void UIExitMenu::draw(sf::RenderWindow& window)
{
	window.draw(image);
	window.draw(saveExit);
	window.draw(cancel);
	window.draw(selectorLeft);
	window.draw(selectorRight);
}

UIExitMenu ::~UIExitMenu(){}