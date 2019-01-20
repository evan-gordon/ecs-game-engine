#include "BagItemNormal.h"

BagItemNormal::BagItemNormal(int position, sf::Texture& img) : BagItem(position, img) {}

BagItemNormal::BagItemNormal(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, int position, sf::Texture& img) : 
	BagItem(ID, pos, spr, position, img)
{
	this->type = NORMAL;
	sprite.setPosition(pos.x, pos.y);
}

BagItemNormal::~BagItemNormal() {}

void BagItemNormal::draw(sf::RenderWindow& window) 
{ 
	window.draw(background);
	window.draw(sprite); 
}