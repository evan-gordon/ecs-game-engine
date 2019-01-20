#include "BagItemLimb.h"

BagItemLimb::BagItemLimb(int position, sf::Texture& img) : BagItem(position, img) {}
BagItemLimb::BagItemLimb(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, LimbSect sect, int position, sf::Texture& img) :
	BagItem(ID, pos, spr, position, img), limbSections(sect) 
{
	this->type = LIMB;
}

BagItemLimb::~BagItemLimb() {}

void BagItemLimb::draw(sf::RenderWindow& window)
{
	window.draw(background);
	limbSections.draw(window, pos);
}