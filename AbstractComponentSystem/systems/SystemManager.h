//Evan Gordon

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <exception>
#include <memory>

#include "Sys.h"
#include "../g_Functions.h"
#include "components/c_WorldObject.h"
#include "components/c_Action.h"
#include "components/Component.h"
#include "components/SavedLocs.h"
#include "s_EntityFactory.h"
#include "../console/Arguments.h"
#include "../console/CManager.h"
#include "../services/Locator.h"

static const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);

//system manager handles startup and shutdown of the game,
//includes saving and loading
class SystemManager
{
private:
	bool exit;
	const bool isGame;
	unsigned int lowestSerial, playerID;
	std::string mapNameAndPath, mapName; 
	Sys sys;
	SavedLocs sLoc;
	std::vector<std::string> broadcastMessages;
	std::shared_ptr<sf::RenderWindow> window;
	sf::View gameView, UIView;
	std::shared_ptr<sf::Event> evnt;
	std::shared_ptr<sf::Font> gameFont;
	sf::Clock gameClock, deltaClock; //no uses for game clock as of yet
	sf::Time deltaTime;
	std::vector<unsigned int> entityList;//ID list of entities spawned in the game
	std::pair<std::string, std::unique_ptr<pugi::xml_document>> mapFile;
	
	s_EntityFactory factory;

public:
	SystemManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> font, const bool& isGame);
	~SystemManager();

	void loadFile(const std::string& mapName);
	void loadMap(const std::string& mapName, const bool& playerAlreadySpawned = false);
	void changeMap(const Arguments& arg);
	void changeMap(const std::string mapName, const float& x = 640, const float& y = 320);
	void saveMap(std::vector<unsigned int>& idsToKeepLoaded);

	void initialize(const std::string& mapName);
	void handleEvents();
	void broadcast();
	StateType update();
	void draw();
	void cleanup();
	void teleportID();

};
#endif