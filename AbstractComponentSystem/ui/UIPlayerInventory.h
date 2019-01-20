//Evan Gordon
#ifndef UIPLAYERINVENTORY_H
#define UIPLAYERINVENTORY_H

#include <memory>
#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "UI.h"
//#include "UIActiveItem_Cursor.h"
//#include "UINewActiveItem_Cursor.h"
#include "elements/Cursor.h"
#include "../systems/s_TileChanger.h"
#include "../systems/s_Inventory.h"
#include "../systems/s_Limb.h"
#include "elements/BagItem.h"
#include "elements/BagItemNormal.h"
#include "elements/BagItemLimb.h"
#include "status.h"

static const sf::Vector2i initialCursorPosPixels = sf::Vector2i(1137, 15);

enum InvState{MOVING, ITEMSELECTED, SWAPPING};

class UIPlayerInventory : public UI
{
private:
	static const int activeItemX;
	static const int activeItemY;
	static const int activeItemMoveDistance;
	static const int inventorySize;
	sf::Font font;

	InvState state;
	int menuPosition;
	short int tileOffset; //this is for keeping track of what number of tile the active item is on
	sf::Vector2i movementVector;
	s_Inventory& inventoryManager;
	s_Graphics& graphicsManager;
	s_Limb& limbManager;
	sf::Texture& img;
	std::vector<std::unique_ptr<BagItem>> bagItems;//type included for conversion, and pointer to object
	std::unique_ptr<BagItem> body;
	
	Cursor currentElement, selectionCursor, menuSelector;

	sf::Sprite& scaleSprite(sf::Sprite& spr);
	void creatLimbSects(LimbSect& sect, const c_Limb& parent);
	void drawLimbMenu(sf::RenderWindow& window);
	void drawItemMenu(sf::RenderWindow& window);
	void drawStatus(sf::RenderWindow& window);
	std::vector<sf::Color> generateOptionsColor();

public:

	UIPlayerInventory(bool canToggle, sf::Texture& invImage, s_Inventory& inventoryManager, 
		s_Graphics& graphicsManager, s_Limb& limbManager);

	virtual bool toggle();
	void moveActiveItem(sf::Vector2i direction);
	virtual void update();
	void draw(sf::RenderWindow& window);
	void setActiveItem();
	void setInventoryLinkAt(int i);
	sf::Vector2f calcPos(const int& position);
	void setItemAtPosition(int position, const c_InventoryItem& invItem);
	void setLimbAtPosition(int position, const c_InventoryItem& invItem, const c_Limb& limb);
	sf::Sprite getCurrentSprite();
	void updateInventorySlot(int position);
	void select();
};

#endif