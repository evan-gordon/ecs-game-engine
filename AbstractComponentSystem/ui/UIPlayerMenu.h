//Evan Gordon

#ifndef UIPLAYERMENU_H
#define UIPLAYERMENU_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include "UI.h"
#include "elements/Cursor.h"
//#include "UIActiveItem_Cursor.h"
//#include "UINewActiveItem_Cursor.h"
//#include "../systems/components/Tile.h"
#include "elements/TileItem.h"
#include "../systems/s_TileChanger.h"
#include "../systems/s_Map.h"//for reading in tile Prefabs

class UIPlayerMenu: public UI
{
private:
	static const int activeItemX;
	static const int activeItemY;
	static const int activeItemMoveDistance;

	int tempItemNumber, activeItemNumber;
	short int tileOffset; //this is for keeping track of what number of tile the active item is on
	unsigned int ID;

	std::vector<std::shared_ptr<TileItem>> menuItems;// prefab tiles
	s_Map& mapManager;

	//UIActiveItem_Cursor activeCursor;
	Cursor currentElement, selectionCursor;
	//UINewActiveItem_Cursor newActiveCursor;

	sf::Vector2i movementVector;
	sf::IntRect itemSize; // rect size of normal item
	pugi::xml_document prefabFile;

public:

	UIPlayerMenu(unsigned int ID, bool canToggle, sf::Texture& menuPanel, s_Map& mapManager);

	virtual bool toggle();
	void moveActiveItem(sf::Vector2i direction);
	virtual void update();
	void draw(sf::RenderWindow& window);
	c_TileChanger setActiveItem(std::string& mapNameAndPath);
	void changePage(bool increasePage);
	bool checkValidPageMovement(bool direction);

	Tile getTile();
};

#endif