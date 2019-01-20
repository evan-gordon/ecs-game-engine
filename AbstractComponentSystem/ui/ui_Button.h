//Evan Gordon

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "../services/Locator.h"

#include <SFML/Graphics.hpp>

#include <stdexcept>
#include <string>

class ui_Button {
private:
    sf::Sprite normal;
    sf::Sprite clicked;
    //sf::Sprite& currentSpr;
    sf::Text text;
	sf::Text font;
    bool isPushed;
	sf::Vector2f location;
	sf::Time delayPush, delay; // delay allows the time to be changed for different buttons

public:
	ui_Button();
	ui_Button(sf::Texture& normal, sf::Texture& clicked, sf::Vector2f location);
    ui_Button (sf::Texture& normal, sf::Texture& clicked, std::string text, sf::Vector2f location, sf::Font& font, sf::Time pressDelay);

    bool checkIfClick (const sf::Vector2f& mousePos);
	bool update (sf::Time deltaTime);
    void setState(bool);
	void setPosition();
	void tog();
	void setSprite(bool newState);
    void setText(std::string);

    bool getState();
    sf::Sprite& getSprite();
    sf::Text& getText();
};

#endif