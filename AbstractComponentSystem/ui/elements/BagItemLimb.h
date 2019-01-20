#ifndef BAGITEMLIMB_H
#define BAGITEMLIMB_H

#include "BagItem.h"
#include <tuple>
#include <memory>

struct LimbSect
{
	sf::Vector2f offset;
	sf::Sprite sprite;
	std::vector<std::shared_ptr<LimbSect>> children;

	LimbSect::LimbSect() : sprite(), offset(0.f, 0.f), children() {}
	void LimbSect::draw(sf::RenderWindow& window, sf::Vector2f pos)
	{
		sf::Vector2f tmpPos(pos.x + offset.x, pos.y + offset.y);
		sprite.setPosition(tmpPos.x, tmpPos.y);
		window.draw(sprite);
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			(*it)->draw(window, tmpPos);
		}
	}

};

class BagItemLimb : public BagItem
{
public:
	BagItemLimb(int position, sf::Texture& img);
	BagItemLimb(unsigned int ID, sf::Vector2f pos, sf::Sprite spr, LimbSect sect, int position, sf::Texture& img);

	~BagItemLimb();

	void draw(sf::RenderWindow& window);

private:
	LimbSect limbSections;
};
#endif

