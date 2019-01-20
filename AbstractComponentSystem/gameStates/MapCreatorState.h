//Evan Gordon

#ifndef MAPCREATORSTATE_H
#define MAPCREATORSTATE_H

#include "../pugixml.hpp"
#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <string>
#include <windows.h>//os specific
#include <direct.h>

#include "IsState.h"
#include "../services/Locator.h"

//change file that is seat as starting file for all new saves
//save generator function is os specific to windows
class MapCreatorState:public IsState
{
private:
	bool nameEntered, widthEntered, heightEntered;//nameEntered is the only one used for creating save
	bool createMap;//true when creating new map
	sf::Sprite background;
	sf::Texture backText;
	pugi::xml_document mapList, newXMLFile, tilePrefab, savesList, campaignMaps;
	sf::Text newFile, width, height, nameInput, wInput, hInput;

public:
	MapCreatorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, 
		const bool& createMap);
	~MapCreatorState();

	void initialize();
	StateType update();
	void draw();
	bool handleEvents();

	void generateMap();
	void generateSave();
};

#endif