//Evan Gordon

#ifndef C_WORLDOBJECT_H
#define C_WORLDOBJECT_H

#include "Component.h"
#include <SFML/Graphics.hpp>

class c_WorldObject:public Component
{
public:
	bool positionAsFloat;
	sf::Vector2f position, dimentions;
	sf::Vector2i positionInTiles;

	c_WorldObject(sf::Vector2f position, sf::Vector2f dimentions);
	c_WorldObject(sf::Vector2i tilePosition, sf::Vector2f dimentions);
	~c_WorldObject();

};

#endif