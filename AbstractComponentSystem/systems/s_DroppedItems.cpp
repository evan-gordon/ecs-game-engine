//Evan Gordon
#include "s_DroppedItems.h"

s_DroppedItems::s_DroppedItems(s_WorldObject& worldObjects, s_Graphics& graphicsManager)
:worldObjectManager(worldObjects), graphicsManager(graphicsManager), components()
{
}

void s_DroppedItems::update()
{
	//dropped item logic. add timer for dropped items so that they cant be picked back up for x period of time?
}

void s_DroppedItems::addItem(unsigned int ID, c_InventoryItem item)
{
	components.insert(std::pair<unsigned int, c_InventoryItem>(ID, item));
}

void s_DroppedItems::removeComponent(unsigned int ID)
{
	components.erase(ID);
}

void s_DroppedItems::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	pugi::xml_node curr = parent.append_child("inventoryitem");
	//c_InventoryItem& itemToSave = components.at(ID);
	//curr.append_child("itemID");//
	//curr.append_child("maxstack");
	//curr.append_child("amount");
	//curr.append_child("value");//
	//curr.append_child("name");//
	//curr.append_child("type");//
	//curr.append_child("desc");//
	//curr.append_child("consumable");//
	//curr.append_child("dropui");
	//curr.append_child("dropparticle");//
	//curr.child("itemID").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.itemId).c_str());//
	//curr.child("maxstack").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.MAX_STACK).c_str());
	//curr.child("amount").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.amount).c_str());
	//curr.child("value").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.value).c_str());//
	//curr.child("name").append_child(pugi::node_pcdata).set_value(itemToSave.type.c_str());//
	//curr.child("type").append_child(pugi::node_pcdata).set_value(itemToSave.type.c_str());//
	//curr.child("desc").append_child(pugi::node_pcdata).set_value(itemToSave.type.c_str());//
	//curr.child("dropui").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.dropUI).c_str());
	//curr.child("dropparticle").append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.dropParticle).c_str());//

	//if (itemToSave.consume.hpChange != 0) {//
	//	curr = curr.child("consumable").append_child("hpChange");
	//	curr.append_child(pugi::node_pcdata).set_value(std::to_string(itemToSave.itemId).c_str());
	//}
}

s_DroppedItems::~s_DroppedItems(){}