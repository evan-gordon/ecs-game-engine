//Evan Gordon

#include "Cursor.h"

Cursor::Cursor()
	:drawCursor(false), toggleCursor(false)/*, moveVector(0, 0), maxIndex(0,0),
		directionToMove(0, 0), locationIndex(1, 1)*/
{}

Cursor::Cursor(sf::Texture& image, sf::IntRect drawImage/*, sf::Vector2i moveDistance, sf::Vector2i maxIndex, sf::Vector2i initialLocation*/, bool draw, LinkedElement * currObj)
	:drawCursor(draw), toggleCursor(false),/* moveVector(moveDistance), maxIndex(maxIndex), initialLocation(initialLocation), */
		/*directionToMove(0, 0), locationIndex(1, 1),*/ cursor(image), currObj(currObj)
{
	cursor.setTextureRect(drawImage);
	cursor.setOrigin(drawImage.width / 2.f, drawImage.height / 2.f);
	//cursor.setPosition((float)initialLocation.x, (float)initialLocation.y);
}

/*void Cursor::moveEvent(sf::Vector2i direction)
{
	if(direction.x <= 1 && direction.x >= -1 && direction.y <= 1 && direction.y >= -1)
	{
	directionToMove = direction;
	}
}*/

//void Cursor::moveOutOfBounds(sf::Vector2i direction) {}

void Cursor::setDrawCursor(bool canDraw)
{
	drawCursor = canDraw;
}

void Cursor::setObj(LinkedElement * newObj)
{
	currObj = newObj;
}

LinkedElement * Cursor::getObj()
{
	return currObj;
}

void Cursor::move(const Direction& d)
{
	auto temp = currObj->getDirection(d);
	if (temp != nullptr)
	{
		currObj = temp;
	}
}

void Cursor::setPosition(const sf::Vector2f& locationInPixels)
{
	cursor.setPosition(locationInPixels.x, locationInPixels.y);
}

/*void Cursor::setPosition(const sf::Vector2i& locationInPixels, const sf::Vector2i& locationIndex)
{
	this->locationIndex = locationIndex;
	cursor.setPosition((float)locationInPixels.x, (float)locationInPixels.y);
}*/

sf::Vector2i Cursor::getLocationInPixels()
{
	sf::Vector2i temp;
	temp.x = (int)(cursor.getPosition().x + 0.5);
	temp.y = (int)(cursor.getPosition().y + 0.5);
	return temp;
}

/*sf::Vector2i& Cursor::getLocationIndex()
{
	return locationIndex;
}*/

void Cursor::toggle()
{
	if(!toggleCursor)
	{
		toggleCursor = true;
	}
}

void Cursor::update()
{
	if(toggleCursor)
	{
		toggleCursor = false;
		if(drawCursor)
		{
			drawCursor = false;
		}
		else
		{
			drawCursor = true;
		}
	}

	/*if(directionToMove.x != 0 || directionToMove.y != 0)
	{
		if(directionToMove.x == 1)//for handling x movements
		{
			directionToMove.x = 0;
			locationIndex.x++;
			if(locationIndex.x > maxIndex.x)
			{
				moveOutOfBounds(sf::Vector2i(1, 0));
			}
			else
			{
				cursor.setPosition(cursor.getPosition().x + moveVector.x, cursor.getPosition().y);
			}
		}
		else if(directionToMove.x == -1)
		{
			directionToMove.x = 0;
			locationIndex.x--;
			if(locationIndex.x < 1)
			{
				moveOutOfBounds(sf::Vector2i(-1, 0));
			}
			else
			{
				cursor.setPosition(cursor.getPosition().x - moveVector.x, cursor.getPosition().y);
			}
		}

		if(directionToMove.y == 1)//for handling y movements
		{
			directionToMove.y = 0;
			locationIndex.y++;
			if(locationIndex.y > maxIndex.y)
			{
				moveOutOfBounds(sf::Vector2i(0, 1));
			}
			else
			{
				cursor.setPosition(cursor.getPosition().x, cursor.getPosition().y + moveVector.y);
			}
		}
		else if(directionToMove.y == -1)
		{
			directionToMove.y = 0;
			locationIndex.y--;
			if(locationIndex.y < 1)
			{
				moveOutOfBounds(sf::Vector2i(0, -1));
			}
			else
			{
				cursor.setPosition(cursor.getPosition().x, cursor.getPosition().y - moveVector.y);
			}
		}
	}*/
}

void Cursor::draw(sf::RenderWindow& window)
{
	if(drawCursor){window.draw(cursor);}
}

Cursor::~Cursor() {}