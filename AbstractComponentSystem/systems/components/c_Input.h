//Evan Gordon

#ifndef C_INPUT_H
#define C_INPUT_H

#include <SFML/Graphics.hpp>

#include "Component.h"

class c_Input:public Component
{
public:
	sf::Event::EventType eventType;
	sf::Keyboard::Key keyboardInput;
	sf::Mouse::Button mouseInput;

	c_Input(sf::Event::EventType type, sf::Keyboard::Key key);
	c_Input(sf::Event::EventType type, sf::Mouse::Button button);
	~c_Input();
};

#endif
