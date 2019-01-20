//Evan Gordon
//Alexander Frisk

#ifndef C_INVENTORYITEM_H
#define C_INVENTORYITEM_H

#include "SFML\Graphics.hpp"

#include "Component.h"
#include "../../ui/status.h"

#include <vector>
#include <string>

//this class is to act as the management class for objects that show up inside the player menu as well as in the world when dropped
//it will be moved back and forth between the inventory system and the system managers world objects map of objects in the world when dropped
class c_InventoryItem :public Component
{
public:
	bool isEmpty;//for use when a slot in a characters inventory is empty
	//int MAX_STACK;
	//std::string type;
	/*std::vector<*/unsigned int/*>*/ ID;

	c_InventoryItem();
	c_InventoryItem(unsigned int itemID/*, const int MAX_STACK, std::string type*/);
};

#endif
