#include "BagItem.h"

BagItem::BagItem(int arrayIndex, sf::Texture& img) : 
	LinkedElement(), active(false), ID(0), sprite(), pos(0, 0), index(arrayIndex), 
		background(img, sf::IntRect( 10, 20, 32, 32)) 
{
	background.setOrigin(16, 16);
}

BagItem::BagItem(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, int arrayIndex, sf::Texture& img) : 
	LinkedElement(), active(true), ID(ID), pos(pos), sprite(spr), index(arrayIndex), 
		background(img, sf::IntRect(16, 15, 32, 32))
{
	background.setOrigin(16, 16);
	sprite.setPosition(pos.x, pos.y);
	background.setPosition(pos.x, pos.y);
}

BagItem::~BagItem() {}

bool BagItem::isActive() { return active; }

t_BagItem BagItem::getType() { return type; }

int BagItem::getIndex() { return index; }
void BagItem::setIndex(int i) { index = i; }

sf::Sprite& BagItem::getSprite() { return sprite; }

const unsigned int& BagItem::getID() { return ID; }

void BagItem::draw(sf::RenderWindow& window) {}

void BagItem::setSpritePosition(float x, float y)
{
	pos.y = x;
	pos.y = y;
	sprite.setPosition(x, y);
	background.setPosition(x, y);
}