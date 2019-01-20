//Evan Gordon
#ifndef S_DROPPEDITEMS_H
#define S_DROPPEDITEMS_H

#include "../pugixml.hpp"

#include <map>

#include "components/c_InventoryItem.h"
#include "s_Graphics.h"
#include "s_WorldObject.h"
#include "../ui/status.h"

class s_DroppedItems
{
public:
	s_WorldObject& worldObjectManager;
	s_Graphics& graphicsManager;
	std::map<unsigned int, c_InventoryItem> components;

	s_DroppedItems(s_WorldObject& worldObjects, s_Graphics& graphicsManager);
	~s_DroppedItems();
	void update();
	void addItem(unsigned int ID, c_InventoryItem item);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);
};

#endif