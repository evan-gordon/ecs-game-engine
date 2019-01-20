//Evan Gordon
#include "s_Inventory.h"

s_Inventory::s_Inventory(s_Action& actionManager, s_WorldObject& worldObjectManager, s_DroppedItems& droppedItemsManager, s_LinkedPosition& linkedPositionManager) :
	actionManager(actionManager), worldObjectManager(worldObjectManager), droppedItemsManager(droppedItemsManager), linkedPositionManager(linkedPositionManager),  inventories()
{}

void s_Inventory::update()//get working here :D
{
	if (inventories.size() == 0 || droppedItemsManager.components.size() == 0){return;}//nothing to compare case

	std::vector<unsigned int> toErase;
	for (auto it = inventories.begin(); it != inventories.end(); it++)//compare each inventory entity to every dropped item
	{
		for (auto droppedIterator = droppedItemsManager.components.begin(); droppedIterator != droppedItemsManager.components.end(); droppedIterator++)
		{
			double result = worldObjectManager.findDistance(droppedIterator->first, it->first);//currently no objects inside worldobjects for some reason
			if ((result / 32.0) <= 0.4)//if its close enough, call some pickup funct
			{
				//insert pickup function 
				int result = pickUp(it->first, droppedIterator->second);
																								
				//0 means remove, any other number should be left on the ground or something. maybe later add a way to set inv as full
				if (result == 0)
				{toErase.push_back(droppedIterator->first);}
			}
			else if ((result / 32.0) <= 1.15)//if it's kinda close, call move towards funct
			{worldObjectManager.moveTowards(droppedIterator->first, it->first, 8);}
		}
	}
	for (auto it = toErase.begin(); it != toErase.end(); it++)//remove all items that were added to inventory
	{
		droppedItemsManager.removeComponent(*it);
	}
}

//Function for adding an item with pickupID for a userID's inventory. Returns an int with the number that didn't fit in inventory
int s_Inventory::pickUp(unsigned int userID, const c_InventoryItem& item)
{
	if (item.isEmpty)
	{ 
		Locator::getConsole().log("Empty item pickup attempted.");
		return -1; 
	}

	if (inventories.find(userID) != inventories.end())//check if inventory exists, if doesnt return -1
	{
		for (auto it = inventories[userID].items.begin(); it != inventories[userID].items.end(); it++)
		{
			if (it->isEmpty)
			{
				*it = item;
				worldObjectManager.setPosition((*it).ID, sf::Vector2f(-3200, -3200));
				return 0;
			}
		}
		Locator::getConsole().log("Inventory for ID: " + std::to_string(userID) + " was full, item not picked up.");
		return 1;
	}
	Locator::getConsole().log("Inventory for ID: " + std::to_string(userID) + " not found, item not picked up.");
	return -1;
}

//Returns the itemID of the item currently in the first location in the inventory -------this will need to be completly reworked for limb system --
unsigned int s_Inventory::getWeapon(unsigned int ID) {

	/*if (inventories.at(ID).size() == 0 || inventories.find(ID) == inventories.end()) //Checks if inventory exists //Checks if there's somehting in the first slot
	{return 0;}

	return inventories[ID].at(0).ID;//Returns the itemID of the first item
	*/
	return 0;
}

//Returns the given item for the userID and position
const c_InventoryItem& s_Inventory::getItem(unsigned int userID, unsigned int position)
{
	if (position < 0 || position >= inventories[userID].items.size())
	{
		Locator::getConsole().log("Invalid invetory position requested, value: " + std::to_string(position));
		return NULL;
	}
	return inventories[userID].items.at(position);
}

//Function called when the selected item is supposed to be equipped
void s_Inventory::equip(unsigned int ID, int position)
{
	//int pos2;
	//c_InventoryItem *item = inventories.at(ID)->items.at(position);
	
	//swapSlot(ID, position, pos2);
}

//Function called when the selected item is supposed to be used
void s_Inventory::use(unsigned int ID, int position)
{
	if (!inventories[ID].items.at(position).isEmpty)
	{
		//do something???
	}	
}

//Currently removes the item from the inventory
//write drop multiple later
void s_Inventory::drop(unsigned int ID, int position = 0)//defaults to first position
{
	if (inventories.find(ID) != inventories.end())
	{
		const c_InventoryItem& toDrop = inventories[ID].items.at(position);
		droppedItemsManager.addItem(toDrop.ID, toDrop);
		auto temp = worldObjectManager.getLocationf(ID);//get direction owner of inv is facing
		const c_Action& invOwner = actionManager.getAction(ID);
		temp.x = temp.x + 1.5f * 32.0f * (float)std::cos((invOwner.lookAngle * M_PI) / 180.0f) + (/*random var up to .4f*/randBetween(0.0f, .4f) * 32.0f );
		temp.y = temp.y + 1.5f * 32.0f * (float)std::sin((invOwner.lookAngle * M_PI) / 180.0f) + (randBetween(0.0f, .4f) * 32.0f);
		worldObjectManager.setPosition(toDrop.ID, temp);
		inventories[ID].items.at(position) = c_InventoryItem();
	}
}

//Private function for switching the content of 2 itemslots in the inventory
//If the position is negative then it means the slot is an equippable slot
void s_Inventory::swapSlot(unsigned int ID, int position1, int position2)
{
	if (position1 < 0 || position2 < 0){return;}

	if (inventories.find(ID) != inventories.end())
	{
		if (inventories[ID].items.size() > position1 && inventories[ID].items.size() > position2)
		{
			const c_InventoryItem temp = inventories[ID].items.at(position1);
			inventories[ID].items.at(position1) = inventories[ID].items.at(position2);
			inventories[ID].items.at(position2) = temp;
		}
	}
}

void s_Inventory::swapItemsById(unsigned int inventoryID, unsigned int IDone, unsigned int IDtwo)
{
	int posOne = -1, posTwo = -1;

	if (inventories.find(inventoryID) != inventories.end())
	{
		auto inv = inventories[inventoryID];

		for (int i = 0; i < inv.items.size(); i++)
		{
			if (!inv.items.at(i).isEmpty && inv.items.at(i).ID == IDone) { posOne = i; }
			if (!inv.items.at(i).isEmpty && inv.items.at(i).ID == IDtwo) { posTwo = i; }

			if (posOne != -1 && posTwo != -1)
			{
				swapSlot(inventoryID, posOne, posTwo);
				break;
			}
		}
	}
}
//make a funtion later for dead characters to drop everything they are holding upon death

//Creates a new inventory and equipment for the entities loaded
//TODO Write a more dynamic version later
void s_Inventory::addComponent(const unsigned int& ID)
{
	inventories.insert(std::make_pair(ID, InvItems(false, 30)));
}

// will remove inventory or item in inventory related to ID given
//note because it deletes whole inventories, caution should be used, use drop to remove a single item
void s_Inventory::removeComponent(unsigned int ID)
{
	inventories.erase(ID);
}

//this function was made in order to get the ids of every item stored in inventory,
//currently it is being used only in entityFactory to determine which items shouldnt be deleted on map switch.
std::vector<unsigned int> s_Inventory::getIDsInInventory(const int& ID)
{
	if (inventories.find(ID) == inventories.end()){return std::vector<unsigned int>();}

	std::vector<unsigned int> result;
	auto comp = inventories[ID];
	for (auto it = comp.items.begin(); it != comp.items.end(); it++)
	{
		if (!(it->isEmpty))
		{result.push_back(it->ID);}
	}
	return result;
}

void s_Inventory::savetoFile(unsigned int ID, pugi::xml_node& parent)
{
	auto curr = parent.append_child("inventory");
}

void s_Inventory::saveInvItem(c_InventoryItem itemToSave, pugi::xml_node& parent)
{
	auto curr = parent.append_child("inventoryitem");
}

s_Inventory::~s_Inventory(){}