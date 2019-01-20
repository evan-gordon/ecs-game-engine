//Evan Gordon

#ifndef S_INVENTORY_H
#define S_INVENTORY_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

#include "components/c_InventoryItem.h"
#include "../g_Functions.h"
#include "s_WorldObject.h"
#include "s_LinkedPosition.h"
#include "s_DroppedItems.h"
#include "s_Action.h"
#include "../ui/status.h"
#include "../services/Locator.h"

//typedef std::pair<std::vector<c_InventoryItem>, std::vector<c_>> items;
struct InvItems
{
	bool hasLimbs;
	int invSize;
	std::vector<c_InventoryItem> items, limbs;

	InvItems::InvItems(bool hasLimbs, int invSize) : 
		hasLimbs(hasLimbs), invSize(invSize), items(invSize, c_InventoryItem())
	{}
};

//Class for managing inventory items, when an item is added to the players inventory it is moved really far out of the map range (-3200, -3200)
//This class also searches the dropped items list for any items that might be in range to pick up for each inventory
class s_Inventory
{
public:
	s_Action& actionManager;
	s_WorldObject& worldObjectManager;
	s_DroppedItems& droppedItemsManager;
	s_LinkedPosition& linkedPositionManager;
	std::map<unsigned int, InvItems> inventories;

	s_Inventory(s_Action& actionManager, s_WorldObject& worldObjectManager, s_DroppedItems& droppedItemsManager, s_LinkedPosition& linkedPositionManager);
	~s_Inventory();

	void update();
	int pickUp(unsigned int ID, const c_InventoryItem& item);
	unsigned int getWeapon(unsigned int ID);
	const c_InventoryItem& getItem(unsigned int userID, unsigned int position);
	void equip(unsigned int ID, int position);
	void use(unsigned int ID, int position);
	void drop(unsigned int ID, int position);
	void addComponent(const unsigned int& ID);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node& parent);
	void saveInvItem(c_InventoryItem item, pugi::xml_node& parent);
	void swapSlot(unsigned int ID, int position1, int position2);
	void swapItemsById(unsigned int inventoryID, unsigned int IDone, unsigned int IDtwo);

	std::vector<unsigned int> getIDsInInventory(const int& ID);

private:
};
#endif