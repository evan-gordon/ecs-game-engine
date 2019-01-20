#ifndef BAGITEMNORMAL_H
#define BAGITEMNORMAL_H

#include "BagItem.h"

#include <SFML/Graphics.hpp>

class BagItemNormal : public BagItem 
{
public:
	BagItemNormal(int position, sf::Texture& img);
	BagItemNormal(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, int position, sf::Texture& img);
	~BagItemNormal();

	void draw(sf::RenderWindow& window);
};

#endif // !BAGITEMNNORMAL_H