//Evan Gordon
//Alexander Frisk
#include "SystemManager.h"

SystemManager::SystemManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> font, const bool& isGame) :
	mapNameAndPath(""), mapName(""), exit(false), isGame(isGame), window(window), gameFont(font), evnt(gameEvent), gameView(sf::FloatRect(0, 0, 1280, 640)), UIView(sf::FloatRect(0, 0, 1280, 640)), lowestSerial(1), deltaTime(), 
		sys(playerID, mapNameAndPath, font, gameEvent, window, gameView, isGame, deltaTime, entityList, UIView), sLoc(mapName, sys.worldObjectManager),
				factory(isGame, entityList, sys)
{}

void SystemManager::initialize(const std::string& mapN)
{	
	//setup console commmands
	//add extendmap, addcomponent, removecomponent
	Locator::getConsole().console.setCommand("summon", std::bind(static_cast<void (s_EntityFactory::*)(const Arguments&)>(&s_EntityFactory::spawnPrefab), &factory, std::placeholders::_1));
	Locator::getConsole().console.setCommand("removeentity", std::bind(static_cast<void (s_EntityFactory::*)(const Arguments&)>(&s_EntityFactory::removeEntity), &factory, std::placeholders::_1));
	Locator::getConsole().console.setCommand("changemap", std::bind(static_cast<void (SystemManager::*)(const Arguments&)>(&SystemManager::changeMap), this, std::placeholders::_1));
	Locator::getConsole().console.setCommand("saveloc", std::bind(static_cast<void (SavedLocs::*)(const Arguments&)>(&SavedLocs::saveLoc), &sLoc, std::placeholders::_1));
	Locator::getConsole().console.setCommand("savelocintiles", std::bind(static_cast<void (SavedLocs::*)(const Arguments&)>(&SavedLocs::saveLocInTiles), &sLoc, std::placeholders::_1));
	Locator::getConsole().console.setCommand("getloc", std::bind(static_cast<void (SavedLocs::*)(const Arguments&)>(&SavedLocs::getLoc), &sLoc, std::placeholders::_1));
	Locator::getConsole().console.setCommand("getlocintiles", std::bind(static_cast<void (SavedLocs::*)(const Arguments&)>(&SavedLocs::getLocInTiles), &sLoc, std::placeholders::_1));

	resetSerial();
	sys.init();
	loadMap(mapN);

	unsigned int pID = sys.nameManager.findByName("player");
	if (pID != 0){playerID = pID;}//set local playerID value to what it actually is

	auto temp = sys.worldObjectManager.getLocationf(playerID);
	gameView.setCenter(temp.x, temp.y);

	auto ids = serializeMultiple(6);
	factory.spawnPrefabAt("testbody", ids.at(0), sf::Vector2f(64, 64));
	factory.spawnPrefabAt("testhead", ids.at(1), sf::Vector2f(32, 32));
	factory.spawnPrefabAt("testlleg", ids.at(2), sf::Vector2f(64, 32));
	factory.spawnPrefabAt("testrleg", ids.at(3), sf::Vector2f(32, 64));
	factory.spawnPrefabAt("testlarm", ids.at(4), sf::Vector2f(0, 0));
	factory.spawnPrefabAt("testrarm", ids.at(5), sf::Vector2f(32, 0));
	/*sys.limbManager.attachTo(ids.at(1), ids.at(0));
	sys.limbManager.attachTo(ids.at(2), ids.at(0));
	sys.limbManager.attachTo(ids.at(3), ids.at(0));
	sys.limbManager.attachTo(ids.at(4), ids.at(0));
	sys.limbManager.attachTo(ids.at(5), ids.at(0));*/
}

//for some reason buffers dont stay loaded, so for now i'll only store one map at a time
//this sets the file name and path for said variable and loads file into memory
void SystemManager::loadFile(const std::string& mapN)//if game is active, then save file is already attached to the front,
{
	if (mapFile.first != mapN)//check if map is already inside mapfile
	{
		mapName = mapN;
		if (!isGame)
		{
			mapNameAndPath = "xml/maps/" + mapN + ".xml";
		}
		else
		{
			mapNameAndPath = "xml/saves/" + mapN + ".xml";
		}//mapname is passed in as <saveFileName>/mapN for this scenario

		mapFile = std::make_pair(mapName, std::unique_ptr<pugi::xml_document>(new pugi::xml_document));
		auto result = mapFile.second->load_file(mapNameAndPath.c_str());
		if (!result)
		{
			Locator::getConsole().log("Load result: " + std::string(result.description()) + ", mesh name: " + mapFile.second->child("mesh").attribute("name").value());
			try
			{throw;}
			catch (std::exception e)
			{
				Locator::getConsole().log("Error: Failed to find " + mapName + " the file was either moved or damaged.");
				return;//document doesnt exist
			}
		}
	}
	return;
}

void SystemManager::loadMap(const std::string& mapName, const bool& playerAlreadySpawned/*defaults to false*/)
{
	loadFile(mapName);
	pugi::xml_node temp = mapFile.second->child("node");
	sys.gameMap.readMap(temp, mapNameAndPath);

	if (!isGame)//items that spawn only for the map editor
	{
		if (!playerAlreadySpawned)
		{
			factory.spawnPrefabAt("player", serialize(), sf::Vector2f(300, 300));//spawns new copy of player that doesnt alter the copy of player that is used when the campaign is being played
			factory.spawnPrefabAt("magicwrench", serialize(), sf::Vector2f(100, 100));
			//factory.spawnPrefabAt("slime", serialize(), sf::Vector2f(50, 300));
		}
		int numOfItemsToSpawn = numberOfNodes(temp.child("items"));
		if (temp.child("items").child("player") != NULL){numOfItemsToSpawn--;}//if player data exists in map data, make sure we arent spawning it

		factory.readItems(temp.child("items"), serializeMultiple(numOfItemsToSpawn), false);//curently items not saving properly
	}
	else//player already spawned should always be true when changing map. and player shouldnt be appearing in save of map when playing
	{
		factory.readItems(temp.child("items"), serializeMultiple(numberOfNodes(temp.child("items"))), true);//curently items not saving properly
	}// every time a map is changed player is read out to xml and moved over to new map	
}

void SystemManager::changeMap(const Arguments& arg){changeMap(arg.strings[0]);}

//might need to optionally take vector of ids
//make sure that mapName includes save file path, if game is being played
void SystemManager::changeMap(const std::string mapName, const float& x, const float& y)
{
	pugi::xml_document mapList;
	if (!mapList.load_file("xml/maps.xml"))//check if mapName exists
	{
		try{throw;}
		catch (std::exception)
		{Locator::getConsole().log("Change Map Request Failed: Unable to open xml/maps.xml for map list reading.");}
	}
	pugi::xml_node listNode = mapList.child("maps");//check if mapName exists


	if (listNode.child(mapName.c_str()) != NULL)//if it does
	{
		//different cases arent needed, player will always be kept loaded
		std::vector<unsigned int> keepLoaded;
		keepLoaded.push_back(playerID);
		saveMap(keepLoaded);
		loadMap(mapName, true);//load new map
		sys.worldObjectManager.setPosition(playerID, sf::Vector2f(x, y));
	}
	else
	{Locator::getConsole().log(mapName + " not found");}
}

void SystemManager::saveMap(std::vector<unsigned int>& idsToKeepLoaded)
{
	loadFile(mapName);
	auto temp = mapFile.second->child("node").child("items");
	factory.saveMap(temp, idsToKeepLoaded);
	//std::string mapXML = "xml/maps/" + gameMap.getMapName() + ".xml";
	mapFile.second->save_file(mapNameAndPath.c_str());
	sys.gameMap.saveMap(mapNameAndPath);
}

void SystemManager::handleEvents()
{
	std::string message;
	while (window->pollEvent(*evnt))
	{
		message = sys.inputManager.update();
		if (message != ""){broadcastMessages.push_back(message);}
	}
	sys.inputManager.updateIsKeyPressed();
}

void SystemManager::broadcast()
{
	for (auto it = broadcastMessages.begin(); it != broadcastMessages.end(); it++)
	{
		if (broadcastMessages[0] == "attack1" && sys.inventoryManager.getWeapon(1) != 0)
		{
			unsigned int currentActiveItem = sys.inventoryManager.getWeapon(1);
			//check all weapon behavior managers for this number, call use func ------------------------------------
			if (sys.tileChangerManager.components.find(currentActiveItem) != sys.tileChangerManager.components.end())
			{
				sys.tileChangerManager.useBehavior(1, currentActiveItem);
			}
		}
	}
	broadcastMessages.clear();
}

StateType SystemManager::update()
{
	deltaTime = deltaClock.restart() + FRAME_TIME;
	sys.update(deltaTime);
	if (sys.portalManager.IDsToTele.size() != 0){ teleportID(); }//check for items to be moved to new map in portal manager
	auto itemsToTele = sys.portalManager.getTeleIDs();
	if (itemsToTele.size() != 0)
	{
		for (auto it = itemsToTele.begin(); it != itemsToTele.end(); it++)
		{
			//call new func for moving items to map
		}
	}

	auto commandNames = Locator::getConsole().console.getCommandNames();
	for (auto it = commandNames.begin(); it != commandNames.end(); it++)//push all commands from console into broadcast
	{broadcastMessages.push_back(*it);}

	if (Locator::getConsoleUI().getCanDraw()){Locator::getConsoleUI().readEventLog();}

	broadcast();
	if (Locator::getConsole().getHasCommand() > 0) { Locator::getConsole().log("Error in Broadcast; not all arguments were read/removed."); }
	if (sys.UIGraphicsManager.exitMenu.exit)
	{
		cleanup();
		return Pop;
	}
	else
	{return None;}
}

void SystemManager::teleportID()
{
	//uncomment this later when tele-ing items is in
	//auto it = portalManager.IDsToTele.begin();
	//while (it != portalManager.IDsToTele.end())
	//{
	//	if (std::get<0>(*it) != 1)
	//	{
	//		//if map != "none"
	//		//move to new map/loc

	//		it = portalManager.IDsToTele.erase(it);//remove
	//	}
	//	else{it++;}
	//}
	//if (portalManager.IDsToTele.size() != 0)
	//{
	//	if (std::get<1>(portalManager.IDsToTele[0]) != "none")
	//	{
	//		changeMap(std::get<1>(portalManager.IDsToTele[0]), std::get<2>(portalManager.IDsToTele[0]).x, std::get<2>(portalManager.IDsToTele[0]).y);
	//		//player exists, tele
	//	}
	//	portalManager.IDsToTele.clear();
	//}
	auto it = sys.portalManager.IDsToTele.begin();//comment all this when the above is uncommented
	while (it != sys.portalManager.IDsToTele.end())
	{
		if (std::get<0>(*it) == 1 && std::get<1>(*it) != "none")
		{
			changeMap(std::get<1>(sys.portalManager.IDsToTele[0]), std::get<2>(sys.portalManager.IDsToTele[0]).x, std::get<2>(sys.portalManager.IDsToTele[0]).y);
		}
		it++;
	}
}

void SystemManager::draw(){sys.draw();}

void SystemManager::cleanup()
{
	Locator::getConsole().console.setCommand("noclip", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("changemap", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("summon", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("removeentity", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("saveloc", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("savelocintiles", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("getloc", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("getlocintiles", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	Locator::getConsole().console.setCommand("linkportal", std::bind(&CManager::invalidCommand, std::ref(Locator::getConsole()), std::placeholders::_1));
	std::vector<unsigned int> temp;//hacky nessisity for now
	saveMap(temp);
	Locator::getSound().stopSong();
}

SystemManager::~SystemManager() {}