#ifndef TILEITEM_H
#define TILEITEM_H

#include <SFML/Graphics.hpp>

#include "LinkedElement.h"
#include "../../systems/components/Tile.h"

class TileItem : public LinkedElement
{
public:
	TileItem::TileItem() : LinkedElement(), t() {}
	TileItem::TileItem(Tile t) : LinkedElement (), t(t) {}
	TileItem::~TileItem() {}
	
	void TileItem::draw(sf::RenderWindow& window) { window.draw(t.graphics.sprite); }
	sf::Sprite& TileItem::getSprite() { return t.graphics.sprite; }
	Tile TileItem::getTile() { return t; }

private:
	Tile t;

};

/*TileItem::TileItem()
{
}

TileItem::~TileItem()
{
}*/

#endif // !TILEITEM_H

