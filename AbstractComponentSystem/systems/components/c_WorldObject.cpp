//Evan Gordon

#include "c_WorldObject.h"

c_WorldObject::c_WorldObject(sf::Vector2f position, sf::Vector2f dimentions)
	:position(position), dimentions(dimentions)
{
positionAsFloat = true;
positionInTiles.x = (int)(position.x / 32.0f);
positionInTiles.y = (int)(position.y / 32.0f);
}

c_WorldObject::c_WorldObject(sf::Vector2i tilePosition, sf::Vector2f dimentions)
	:positionInTiles(tilePosition), dimentions(dimentions)
{
positionAsFloat = false;
position = static_cast<sf::Vector2f>(positionInTiles);
position.x = position.x * 32.0f;
position.y = position.y * 32.0f;
}

c_WorldObject::~c_WorldObject() {}