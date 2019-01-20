//Evan Gordon

#include "s_EntityFactory.h"

s_EntityFactory::s_EntityFactory(bool isGame, std::vector<unsigned int>& entityList, Sys& sys) :
	isGame(isGame), entityList(entityList), sys(sys)//, playerOldNode()
{
	if (!charPrefab.load_file("xml/characters.xml"))
	{
		try { throw; }
		catch (std::exception)
		{
			Locator::getConsole().log("serialize failed to read in .xml prefab file.");
		}
	}
	charNode = charPrefab.child("prefab");
	readFuncs.insert(std::make_pair("name", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_Name), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("worldobject", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_worldObject), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("health", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_health), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("damager", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_damager), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("physics", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_physics), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("action", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_action), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("ai", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_ai), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("limb", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_limb), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("bodysocket", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_bodySocket), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("uigraphics", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_uigraphics), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("portal", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_portal), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("graphics", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_graphics), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("inventoryitem", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_inventoryItem), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("inventory", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_inventory), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("tilechanger", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_tileChanger), this, std::placeholders::_1, std::placeholders::_2)));
	readFuncs.insert(std::make_pair("", std::bind(static_cast<void(s_EntityFactory::*)(const unsigned int&, const pugi::xml_node&)>(&s_EntityFactory::f_default), this, std::placeholders::_1, std::placeholders::_2)));

}
//for reading items from a .xml file
void s_EntityFactory::readItems(pugi::xml_node parent, std::vector<unsigned int> IDS, bool isGame)
{
	if (IDS.size() == 0) { return; }

	std::string nodeName;
	for (auto node = parent.first_child(); node; node = node.next_sibling())
	{
		nodeName = node.child("name").first_child().name();
		if (nodeName == ""){ Locator::getConsole().log("Invalid name component"); break; }

		if (isGame || nodeName != "player")
		{
			convertPrefab(node, IDS[0]);//xD i was spawning the default prefabs
			IDS.erase(IDS.begin());
		}
	}
}

//Search through characters.xml for a prefab node with given name, return node.
pugi::xml_node s_EntityFactory::findPrefab(std::string name)
{
	for (auto curr = charNode.first_child(); curr; curr = curr.next_sibling())
	{
		Locator::getConsole().log("Found " + std::string(curr.name()));
		if (curr.name() == name)
		{return curr;}
	}
	Locator::getConsole().log("Error prefab " + name + " not found.");
	pugi::xml_node nullNode;//might not work
	return nullNode;
}

//For each Entity node check if it had an inventory node, if it does check how many nodes are in that
int s_EntityFactory::findInventoyItems(pugi::xml_node items)
{
	int counter = 0;
	//find all entities w inventories, and see how many nodes are inside
	for (pugi::xml_node curr = items.first_child(); curr; curr = curr.next_sibling())//entity traversal
	{
		for (curr = curr.first_child(); curr; curr = curr.next_sibling())//component traversal
		{
			if (curr.name() == "inventory")
			{
				for (curr = curr.first_child(); curr; curr = curr.next_sibling())//stored entity traversal
				{counter++;}

				curr = curr.parent();
			}
		}
		curr = curr.parent();
	}
	return counter;
}

//for use with only console commands
void s_EntityFactory::spawnPrefab(const Arguments& arg/*, unsigned int ID, sf::Vector2f playerLoc*/)
{
	if (arg.ints.size() == 0)
	{
		spawnPrefabAt(arg.strings[0], serialize(), sys.worldObjectManager.getLocationf(1));
		return;
	}
	sf::Vector2f temp((float)arg.ints[0], (float)arg.ints[1]);
	spawnPrefabAt(arg.strings[0], serialize(), temp);
}

//create an overloaded version that adds a item type, also another overloaded version for spawning multiple at once (perhaps used for particles?"
//this is suppost to only be used for spawining from prefab file xD

bool s_EntityFactory::spawnPrefabAt(std::string name, const unsigned int& ID, sf::Vector2f loc)
{
	bool succeded = spawnPrefab(name, ID);
	if (succeded)
	{
		sys.worldObjectManager.setPosition(ID, loc);
		sys.graphicsManager.components[ID].sprite.setPosition(loc);
		return true;
	}
	return false;
}

bool s_EntityFactory::spawnPrefab(std::string name, const unsigned int& ID)
{
	for (pugi::xml_node curr = charNode.first_child(); curr; curr = curr.next_sibling())
	{
		if (curr.name() == name)
		{
			convertPrefab(curr, ID);
			Locator::getConsole().log("Spawning " + name + "with ID: " + std::to_string(ID));
			return true;
		}
	}
	Locator::getConsole().log("Error prefab " + name + " not found; no item spawned.");
	return false;
}

void s_EntityFactory::readLimbSection(const pugi::xml_node& parent, unsigned int parentID)
{
	auto curr = parent.first_child();//pointing to type
	for (curr = curr.next_sibling(); curr; curr = curr.next_sibling())//for each socket
	{
		auto sockData = curr.child("child");//pointing to child
		if (sockData.text().as_string() != "empty")
		{
			if (sockData.child("limb") == NULL)
			{
				Locator::getConsole().log("Error in xml parsing of child limb.");
				return;
			}
			unsigned int childID = serialize();
			convertPrefab(sockData, childID);
			sys.limbManager.attachTo(childID, parentID);//connect to parent
		}
	}
}

void s_EntityFactory::f_Name(const unsigned int& ID , const pugi::xml_node& parent)
{
	std::string temp = parent.first_child().name();
	sys.nameManager.addComponent(ID, c_Name(temp));
}

void s_EntityFactory::f_worldObject(const unsigned int& ID, const pugi::xml_node& parent)
{
	bool asFloat = parent.child("asfloat").text().as_bool();
	if (asFloat)
	{
		sf::Vector2f location, size;
		location.x = parent.child("x").text().as_float();
		location.y = parent.child("y").text().as_float();
		size.x = (float)parent.child("width").text().as_int();
		size.y = (float)parent.child("height").text().as_int();
		sys.worldObjectManager.addComponent(ID, c_WorldObject(location, size));
	}
	else //read in as int
	{
		sf::Vector2f size;
		sf::Vector2i location;
		location.x = parent.child("x").text().as_int();
		location.y = parent.child("y").text().as_int();
		size.x = (float)parent.child("width").text().as_int();
		size.y = (float)parent.child("height").text().as_int();
		sys.worldObjectManager.addComponent(ID, c_WorldObject(location, size));
	}
}

void s_EntityFactory::f_health(const unsigned int& ID, const pugi::xml_node& parent)
{
	int maxHealth = (float)parent.child("max").text().as_int();
	int currMax = (float)parent.child("cmax").text().as_int();
	int curr = (float)parent.child("curr").text().as_int();

	sys.healthManager.addComponent(ID, c_Health(curr, currMax, maxHealth));
}

void s_EntityFactory::f_damager(const unsigned int& ID, const pugi::xml_node& parent)
{
	int dmg = parent.child("dmg").text().as_int();
	int delay = parent.child("delay").text().as_int();

	sys.damageManager.addComponent(ID, c_Damager(dmg, delay));
}

void s_EntityFactory::f_physics(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.physicsManager.addComponent(ID, c_Physics((float)parent.child("maxvelocity").text().as_int()));
}

void s_EntityFactory::f_action(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.actionManager.addComponent(ID, c_Action());
}

void s_EntityFactory::f_ai(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.aiManager.addComponent(ID, parent.first_child().name());
}

void s_EntityFactory::f_limb(const unsigned int& ID, const pugi::xml_node& parent)
{
	auto curr = parent.first_child();//currently set to limb type
	t_Limb currType = sys.limbManager.to_Type(parent.child("type").text().as_string());
	std::vector<std::pair<t_Limb, sf::Vector2f>> sockets = {};
	for (curr = curr.next_sibling(); curr; curr = curr.next_sibling())//should always be at least one
	{
		auto sock = curr.first_child();
		t_Limb type = sys.limbManager.to_Type(sock.text().as_string());
		sock = curr.child("offset");//points to offset
		auto offset = sf::Vector2f(sock.child("x").text().as_float(), sock.child("y").text().as_float());
		sockets.push_back(std::make_pair(type, offset));
	}
	sys.limbManager.addComponent(ID, c_Limb(ID, currType, sockets));
	readLimbSection(parent, ID);//recurse and read limbs
}

void s_EntityFactory::f_bodySocket(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.limbManager.addBodySocket(ID);
}

void s_EntityFactory::f_uigraphics(const unsigned int& ID, const pugi::xml_node& parent)
{
	for (auto curr = parent.first_child(); curr; curr = curr.next_sibling())
	{
		std::string type = curr.name();
		if (type != "")
		{
			sys.UIGraphicsManager.addComponent(ID, type);
		}
	}
}

void s_EntityFactory::f_portal(const unsigned int& ID, const pugi::xml_node& parent)
{
	sf::Vector2f exitLocation;
	std::string mapName = parent.child_value("mapname");
	exitLocation.x = parent.child("x").text().as_float();
	exitLocation.y = parent.child("y").text().as_float();
	sys.portalManager.addComponent(ID, c_Portal(mapName, exitLocation));
}

void s_EntityFactory::f_graphics(const unsigned int& ID, const pugi::xml_node& parent)
{
	sf::Vector2f location, size, origin;
	std::string texture = parent.child_value("texture");
	location.x = (float)parent.child("x").text().as_int();
	location.y = (float)parent.child("y").text().as_int();
	size.x = (float)parent.child("width").text().as_int();
	size.y = (float)parent.child("height").text().as_int();
	origin.x = (float)parent.child("originx").text().as_int();
	origin.y = (float)parent.child("originy").text().as_int();
	//http://www.sfml-dev.org/learn.php	
	if (ID == 1)
	{
		sf::Vector2f temp = sys.worldObjectManager.sorter.find(1)->position;
		sys.graphicsManager.gameView.setCenter(temp.x, temp.y);
	}
	sys.graphicsManager.addComponent(ID, c_Graphics(sys.graphicsManager.textures[texture], texture, 
		sf::Rect<int>((int)location.x, (int)location.y, (int)size.x, (int)size.y), origin));
}

void s_EntityFactory::f_inventoryItem(const unsigned int& ID, const pugi::xml_node& parent)
{
	c_InventoryItem temp(ID);
	sys.droppedItemsManager.addItem(ID, temp);
}

void s_EntityFactory::f_inventory(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.inventoryManager.addComponent(ID);

	auto prefab = parent.parent();
	if (!isGame && (prefab.name() == "player")){return;}//don't spawn player's inventory if in mapmaker

	for (auto storedItems = parent.first_child(); storedItems; storedItems = storedItems.next_sibling())
	{
		auto newID = serialize();
		convertPrefab(storedItems, newID);//spawn new entities
		//(if i revert to old inv sys)when saving wrench is losing its inventory item compnent, fix this, add it to dropped items then move it to inventory
		sys.inventoryManager.pickUp(ID, sys.droppedItemsManager.components[newID]);//add to inventory
		//droppedItemsManager.removeComponent(newID);//remove from ground
	}
}

void s_EntityFactory::f_tileChanger(const unsigned int& ID, const pugi::xml_node& parent)
{
	sys.tileChangerManager.addComponent(ID, parent.first_child());
}

void s_EntityFactory::f_default(const unsigned int& ID, const pugi::xml_node& parent)
{
	std::string componentName = parent.name();
	Locator::getConsole().log("Component " + componentName + " could not be found; component not added.");
}

void s_EntityFactory::convertPrefab(pugi::xml_node prefab, const unsigned int& ID)
{
	entityList.push_back(ID);

	for (auto components = prefab.first_child(); components; components = components.next_sibling())
	{
		std::string componentName = components.name();
		Locator::getConsole().log("Converting " + componentName + ".");
		readFuncs[componentName](ID, components);
		
	}
	Locator::getConsole().log("Spawning " + std::string(prefab.name()));
}//fix this function so that it properly saves all entities, inside another entity's inventory to the correct location in the xml file

 //search through each system, save and delete each component
void s_EntityFactory::saveMap(pugi::xml_node& node, std::vector<unsigned int>& idsToKeepLoaded)
{
	pugi::xml_node curr = node;

	if (isGame)//if game was being played, delete all nodes (to be overwritten later)
	{
		while (node.begin() != node.end()){node.remove_child(node.first_child().name());}

		saveInventories(curr, idsToKeepLoaded);//save all entities with inventories
	}
	else//dont save new info related to player in map editor
	{
		std::string currNodeName = node.first_child().name();

		//delete old information stored in items node, player node may be kept if game mode that was played was mapmaker
		while (node.begin() != node.end())//delete nodes until player node is first or delete everything if player isnt currently saved in map
		{
			if (currNodeName != "player")
			{
				node.remove_child(node.first_child().name());
				currNodeName = node.first_child().name();
			}
			else
			{break;}
		}

		auto it = node.begin();
		if (it != node.end())
		{
			it++;
			while (it != node.end())//delete nodes that are after player
			{
				node.remove_child(it->name());
				it = node.begin();
				it++;
			}
		}

		//remove mapmaker only items here; i.e delete player and magic wrench from all systems
		auto pID = sys.nameManager.findByName("player");
		if (pID != 0 && std::find(idsToKeepLoaded.begin(), idsToKeepLoaded.end(), pID) == idsToKeepLoaded.end()){removeEntity(pID);}//dont delete if keepPlayerLoaded

		//save inventories needs to be here, so that if the wrench is in the players inv when moving map, it will stay loaded
		//because save inventories will add wrench id to list of ids to keep
		saveInventories(curr, idsToKeepLoaded);//save all entities with inventories
		unsigned int wrenchID = -1;//there may be more than one wrench
		while(wrenchID != 0)
		{
			wrenchID = sys.nameManager.findByName("magicwrench");
			if (wrenchID != 0 && std::find(idsToKeepLoaded.begin(), idsToKeepLoaded.end(), wrenchID) == idsToKeepLoaded.end())
			{removeEntity(wrenchID);}
		}
	}

	std::vector<unsigned int> itemsToRemove;//code below wont need to check for inventory components
	for (auto it = entityList.begin(); it != entityList.end(); it++)
	{
		if (std::find(idsToKeepLoaded.begin(), idsToKeepLoaded.end(), *it) == idsToKeepLoaded.end())//check if id is not in list of id's to keep
		{
			saveEntity(*it, curr);
			itemsToRemove.push_back(*it);
		}
	}

	for (auto iterator = itemsToRemove.begin(); iterator != itemsToRemove.end(); iterator++)//delete from list
	{removeEntity(*iterator);}
}

bool s_EntityFactory::saveEntity(const unsigned int& ID, pugi::xml_node& parent)
{
	pugi::xml_node curr;
	if (sys.nameManager.components.find(ID) != sys.nameManager.components.end())
	{
		std::string nameTag = sys.nameManager.getName(ID) + std::to_string(ID);
		curr = parent.append_child(nameTag.c_str());//the added id will ensure tag is unique for each element
		sys.nameManager.savetoFile(ID, curr);
	}
	else
	{
		Locator::getConsole().log("Error: Entity is missing its Name component; Entity not read.");
		return false;
	}

	//evidence that systems may require a base class with saveToFile and find(id) func
	if (sys.worldObjectManager.sorter.find(ID) != NULL)
	{
		sys.worldObjectManager.savetoFile(ID, curr);
	}
	if (sys.healthManager.components.find(ID) != sys.healthManager.components.end())
	{
		sys.healthManager.saveToFile(ID, curr);
	}
	if (sys.damageManager.components.find(ID) != sys.damageManager.components.end())
	{
		sys.damageManager.saveToFile(ID, curr);
	}
	if (sys.physicsManager.components.find(ID) != sys.physicsManager.components.end())//<----move this check into the savetofile func for all
	{
		sys.physicsManager.savetoFile(ID, curr);
	}
	if (sys.actionManager.components.find(ID) != sys.actionManager.components.end())
	{
		sys.actionManager.savetoFile(curr);
	}
	if (sys.aiManager.components.find(ID) != sys.aiManager.components.end())
	{
		sys.aiManager.saveToFile(ID, curr);
	}
	if (sys.inventoryManager.inventories.find(ID) != sys.inventoryManager.inventories.end())
	{
		sys.inventoryManager.savetoFile(ID, curr);
	}
	if (sys.UIGraphicsManager.components.find(ID) != sys.UIGraphicsManager.components.end())
	{
		sys.UIGraphicsManager.savetoFile(ID, curr);
	}
	if (sys.graphicsManager.components.find(ID) != sys.graphicsManager.components.end())
	{
		sys.graphicsManager.savetoFile(ID, curr);
	}
	if (sys.droppedItemsManager.components.find(ID) != sys.droppedItemsManager.components.end())
	{
		sys.droppedItemsManager.savetoFile(ID, curr);
	}
	if (sys.portalManager.components.find(ID) != sys.portalManager.components.end())
	{sys.portalManager.savetoFile(ID, curr);}
	if (sys.tileChangerManager.components.find(ID) != sys.tileChangerManager.components.end())
	{sys.tileChangerManager.savetoFile(ID, curr);}
	return true;
}

//should i rework saving so that works recursively, and doesnt require calling before all entities without inventories?
//for now all this does is find the id's of items w inventories, and call saveEntity, will need rework if inventory changes are reverted
//saves all entities with an inventory, if item has inventory, needs to go through and get every id stored in inventory 
//and add it to ids to keep loaded list, that way it will not be deleted when map changes
void s_EntityFactory::saveInventories(pugi::xml_node& parent, std::vector<unsigned int>& idsToKeepLoaded)
{
	auto curr = parent;
	std::vector<unsigned int> itemsToRemove;
	for (auto it = sys.inventoryManager.inventories.begin(); it != sys.inventoryManager.inventories.end(); it++)//iterate through entities w/ inventories
	{
		//check if id is not in idtokeeploaded list
		//bug in here that causes crash when switching map and item is in inventory
		if (std::find(idsToKeepLoaded.begin(), idsToKeepLoaded.end(), it->first) == idsToKeepLoaded.end())
		{
			saveEntity(it->first, parent);
			//if (nameManager.components.find(it->first) != nameManager.components.end())
			//{
			//	nameManager.savetoFile(it->first, curr);
			//	curr = curr.child(nameManager.getName(it->first).c_str());
			//}
			//else
			//{
			//	log.push("Error: Entity is missing its Name component; Entity not read.");
			//	break;
			//}

			//if (worldObjectManager.sorter.find(it->first) != NULL)
			//{
			//	worldObjectManager.savetoFile(it->first, curr);
			//}
			//if (physicsManager.components.find(it->first) != physicsManager.components.end())
			//{
			//	physicsManager.savetoFile(it->first, curr);
			//}
			//if (actionManager.components.find(it->first) != actionManager.components.end())
			//{
			//	actionManager.savetoFile(curr);
			//}
			//if (UIGraphicsManager.components.find(it->first) != UIGraphicsManager.components.end())
			//{
			//	UIGraphicsManager.savetoFile(it->first, curr);
			//}
			//inventoryManager.savetoFile(it->first, curr);//save inventory
			//if (graphicsManager.components.find(it->first) != graphicsManager.components.end())
			//{
			//	graphicsManager.savetoFile(it->first, curr);
			//}
			//if (droppedItemsManager.components.find(it->first) != droppedItemsManager.components.end())
			//{
			//	droppedItemsManager.savetoFile(it->first, curr);
			//}
			//if (portalManager.components.find(it->first) != portalManager.components.end())
			//{
			//	portalManager.savetoFile(it->first, curr);
			//}
			//if (tileChangerManager.components.find(it->first) != tileChangerManager.components.end())
			//{
			//	tileChangerManager.savetoFile(it->first, curr);
			//}
			//save all items in inventory
			//curr = curr.child("inventory");
			//iterate over items in an inventory
			//for (auto invIterator = inventoryManager.inventories[it->first]->items.begin(); invIterator != inventoryManager.inventories[it->first].end(); invIterator++)
			//for (auto invIterator = inventoryManager.inventories.begin(); invIterator != inventoryManager.inventories.end(); invIterator++)
			//{
			//	inventoryManager.savetoFile(invIterator->first, curr);
				//for (auto invItemIt = invIterator->stackIDs.begin(); invItemIt != invIterator->stackIDs.end(); invItemIt++)//iterate over multiple items of one type
				//{
					////save this item
					//if (nameManager.components.find(*invItemIt) != nameManager.components.end())
					//{
					//	nameManager.savetoFile(*invItemIt, curr);
					//	curr = curr.child(nameManager.getName(*invItemIt).c_str());
					//}
					//else
					//{
					//	log.push("Error: Entity is missing its Name component; Entity not read.");
					//	break;
					//}

					//if (worldObjectManager.sorter.find(*invItemIt) != NULL)
					//{
					//	worldObjectManager.savetoFile(*invItemIt, curr);
					//}
					//if (physicsManager.components.find(*invItemIt) != physicsManager.components.end())
					//{
					//	physicsManager.savetoFile(*invItemIt, curr);
					//}
					//if (actionManager.components.find(*invItemIt) != actionManager.components.end())
					//{
					//	actionManager.savetoFile(curr);
					//}
					//if (UIGraphicsManager.components.find(*invItemIt) != UIGraphicsManager.components.end())
					//{
					//	UIGraphicsManager.savetoFile(*invItemIt, curr);
					//}
					//if (portalManager.components.find(*invItemIt) != portalManager.components.end())
					//{
					//	portalManager.savetoFile(*invItemIt, curr);
					//}
					//if (graphicsManager.components.find(*invItemIt) != graphicsManager.components.end())
					//{
					//	graphicsManager.savetoFile(*invItemIt, curr);
					//}
					//save current inventory item here
					//inventoryManager.saveInvItem(*invIterator, curr);//check this
					//if (tileChangerManager.components.find(*invItemIt) != tileChangerManager.components.end())
					//{
					//	tileChangerManager.savetoFile(*invItemIt, curr);
					//}
					//itemsToRemove.push_back(*invItemIt);
				//}
			//}
			//curr = curr.parent().parent();
			itemsToRemove.push_back(it->first);
		}
		//else//not supposed to delete this entity w/ inventory, or elements in its inventory
		//{
		//	std::vector<unsigned int> temp = inventoryManager.getIDsInInventory(it->first);
		//	if (temp.size() != 0)
		//	{
		//		idsToKeepLoaded.insert(idsToKeepLoaded.end(), temp.begin(), temp.end());//add all id's stored in this inventory to list of items to keep
		//	}
		//}
	}
	//delete
	for (auto iterator = itemsToRemove.begin(); iterator != itemsToRemove.end(); iterator++)
	{
		removeEntity(*iterator);
		//inventoryManager.removeComponent(*iterator);
	}

}

void s_EntityFactory::removeEntity(const Arguments& args){removeEntity(args.ints[0]);}

void s_EntityFactory::removeEntity(const unsigned int& ID)
{
	bool exists = false;
	for (auto it = entityList.begin(); it != entityList.end();)
	{
		if (*it == ID)
		{
			exists = true;
			it = entityList.erase(it);//assigns it ref to next valid node
			break;
		}
		else
		{it++;}
	}
	if (!exists)
	{
		Locator::getConsole().log("Entity " + std::to_string(ID) + " does not exist; nothing removed.");
		return;
	}
	//TODO add for limb
	sys.nameManager.removeComponent(ID);
	sys.worldObjectManager.removeComponent(ID);
	sys.healthManager.removeComponent(ID);
	sys.damageManager.removeComponent(ID);
	sys.physicsManager.removeComponent(ID);
	sys.actionManager.removeComponent(ID);
	sys.aiManager.removeComponent(ID);
	sys.UIGraphicsManager.removeComponent(ID);
	sys.graphicsManager.removeComponent(ID);
	sys.droppedItemsManager.removeComponent(ID);
	sys.inventoryManager.removeComponent(ID);
	sys.tileChangerManager.removeComponent(ID);
	sys.portalManager.removeComponent(ID);
}

s_EntityFactory::~s_EntityFactory() {}