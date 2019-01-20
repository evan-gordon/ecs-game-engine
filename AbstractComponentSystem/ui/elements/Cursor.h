//Evan Gordon

//This is a base class for a cursor
//current uses are for the active and newActiveItem in the UIPlayerMenu
//this object acts as a cursor for objects and is meant to be flexible
#ifndef CURSOR_H
#define CURSOR_H

#include "LinkedElement.h"

#include <SFML/Graphics.hpp>

class Cursor
{
protected:
	bool drawCursor, toggleCursor;
	sf::Sprite cursor;
	//sf::Vector2i /*directionToMove, locationIndex, moveVector, maxIndex,*/ initialLocation;
	LinkedElement * currObj;

public:
	Cursor();
	Cursor(sf::Texture& image, sf::IntRect drawImage,/* sf::Vector2i moveDistance, sf::Vector2i maxIndex, sf::Vector2i initialLocation,*/ bool draw, LinkedElement * currObj);
	virtual ~Cursor();

	//void moveEvent(sf::Vector2i direction);
	//virtual void moveOutOfBounds(sf::Vector2i direction) = 0;

	void setDrawCursor(bool canDraw);
	void setObj(LinkedElement * newObj);

	LinkedElement * getObj();

	void move(const Direction& d);
	void setPosition(const sf::Vector2f& locationInPixels);
	//void setPosition(const sf::Vector2i& locationInPixels, const sf::Vector2i& locationIndex);

	sf::Vector2i getLocationInPixels();
	//sf::Vector2i& getLocationIndex();

	void toggle();
	void update();
	void draw(sf::RenderWindow& window);
};

#endif