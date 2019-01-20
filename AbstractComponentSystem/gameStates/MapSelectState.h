//Evan Gordon

#ifndef MAPSELECTSTATE_H
#define MAPSELECTSTATE_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <exception>
#include <vector>
#include <iostream>

#include "IsState.h"
#include "../g_Functions.h"
#include "../services/Locator.h"

class MapSelectState:public IsState
{
private:
	bool changeMap, loadMap, exit;//load map alternates between chosing to load map or saves game file. so this can act like 2 different states
	int currentMap;
	std::string selectedMapName;
	sf::Text pressN;
	std::vector<sf::Text> mapList;
	sf::Texture listSelectTexture;
	sf::Sprite selector;
	sf::Keyboard::Key up, down, select;

	pugi::xml_document listFile, inputFile;
	pugi::xml_node listNode, inputNode;
public:
	bool newMap; 

	MapSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, bool loadMap);
	~MapSelectState();

	void initialize();
	StateType update();
	void draw();
	bool handleEvents();
	void readList();
	void moveList(bool down);

	void setLoadCondition(bool loadMap);
	bool getLoadCondition();
	std::string getSelectedMapName();
};

#endif