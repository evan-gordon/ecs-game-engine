//Evan Gordon

#ifndef S_TILECHANGER_H
#define S_TILECHANGER_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <map>
#include <iostream>

#include "components/c_TileChanger.h"
#include "s_Map.h"
#include "s_WorldObject.h"

class s_TileChanger
{
public:
	std::string& mapNameAndPath;
	s_Map& mapManager;
	s_WorldObject& worldObjectManager;

	std::map<unsigned int, c_TileChanger> components;

	s_TileChanger(std::string& mapNaF, s_Map& mapManager, s_WorldObject& worldObjectManager);
	void useBehavior(unsigned int userID, unsigned int itemID);
	void changeTile(unsigned int ID, pugi::xml_node tile);
	void changeTile(unsigned int ID, c_TileChanger newTile);
	void addComponent(unsigned int ID, pugi::xml_node tile);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);
};

#endif
