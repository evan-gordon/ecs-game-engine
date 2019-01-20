//Evan Gordon

#ifndef C_LINKEDPOSITION_H
#define C_LINKEDPOSITION_H

#include <SFML/Graphics.hpp>

#include "Component.h"

class c_LinkedPosition:public Component
{
public:
	bool offset;
	sf::Vector2f offsetVal;

	c_LinkedPosition(bool offset, sf::Vector2f val);
	~c_LinkedPosition();
};

#endif