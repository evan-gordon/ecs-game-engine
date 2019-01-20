#ifndef BAGITEM_H
#define BAGITEM_H

#include "LinkedElement.h"

#include <SFML/Graphics.hpp>

enum t_BagItem { NORMAL, LIMB };//add more later as needed

class BagItem : public LinkedElement
{
public:
	BagItem(int arrayLoc, sf::Texture& img);
	BagItem(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, int arrayLoc, sf::Texture& img);
	virtual ~BagItem();

	bool isActive();
	int getIndex();
	void setIndex(int i);
	t_BagItem getType();
	sf::Sprite& getSprite();
	const unsigned int& getID();
	virtual void draw(sf::RenderWindow& window) = 0;
	void setSpritePosition(float x, float y);

protected:
	bool active;		// which items are active in 
	int index;
	unsigned int ID;	//id of item
	t_BagItem type;
	sf::Sprite sprite, background;	// images of items in inventory
	sf::Vector2f pos;
};

#endif // !BAGITEM_H
