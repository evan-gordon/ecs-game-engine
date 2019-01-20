//Evan Gordon
#include "Sys.h"

Sys::Sys(const unsigned int& playerID, std::string& mapNameAndPath, std::shared_ptr<sf::Font> font, std::shared_ptr<sf::Event> evnt, std::shared_ptr<sf::RenderWindow> window, sf::View& gameView, const bool& isGame, sf::Time& deltaTime, const std::vector<unsigned int>& entityList, sf::View& UIView) :
worldObjectManager(), healthManager(), soundManager(worldObjectManager, playerID), gameMap(window, gameView, isGame),
graphicsManager(worldObjectManager, gameView, window), damageManager(worldObjectManager, graphicsManager, healthManager), actionManager(), nameManager(), physicsManager(worldObjectManager, graphicsManager, actionManager, gameMap, deltaTime),
targetEntityManger(entityList), linkedPositionManager(worldObjectManager, targetEntityManger), limbManager(linkedPositionManager), droppedItemsManager(worldObjectManager, graphicsManager),
inventoryManager(actionManager, worldObjectManager, droppedItemsManager, linkedPositionManager), portalManager(worldObjectManager, gameMap, graphicsManager), tileChangerManager(mapNameAndPath, gameMap, worldObjectManager),
UIGraphicsManager(mapNameAndPath, UIView, window, font, gameMap, tileChangerManager, inventoryManager, graphicsManager, limbManager),
inputManager(evnt, physicsManager.components, actionManager, inventoryManager, UIGraphicsManager, soundManager), aiManager(actionManager)
{}

Sys::~Sys(){}

void Sys::init()
{
	Locator::getConsole().console.setCommand("noclip", std::bind(static_cast<void (s_Map::*)(const Arguments&)>(&s_Map::noClip), &gameMap, std::placeholders::_1));
	Locator::getConsole().console.setCommand("linkportal", std::bind(static_cast<void (s_Portal::*)(const Arguments&)>(&s_Portal::linkPortal), &portalManager, std::placeholders::_1));

	inputManager.readFromFile();
	Locator::getSound().playPlaylist(CHEERY);
}

void Sys::update(const sf::Time& dt)
{
	aiManager.update(dt.asMilliseconds());
	physicsManager.update();
	damageManager.update(dt.asMilliseconds());
	limbManager.update();
	droppedItemsManager.update();
	inventoryManager.update();
	linkedPositionManager.update();
	portalManager.update();

	Locator::getSound().updateSong();
}

void Sys::draw()
{
	gameMap.update();
	graphicsManager.update();
	UIGraphicsManager.update();
}