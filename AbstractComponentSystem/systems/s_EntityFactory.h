//Evan Gordon

#ifndef S_ENTITYFACTORY_H
#define S_ENTITYFACTORY_H

#include <algorithm>
#include <vector>
#include <string>
#include <exception>
#include <utility>

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include "components/Component.h"
#include "components/c_WorldObject.h"
#include "components/c_Physics.h"
#include "components/c_Input.h"
#include "components/c_Action.h"
#include "../services/Locator.h"
#include "../console/Arguments.h"
#include "../g_Functions.h"
#include "Sys.h"

typedef std::function<void(const unsigned int&, const pugi::xml_node&)> ReadFunc;

//currently this class reads in the names of all currently stored prefabs, it will also contain a "perscription method"
//the perscription method will be able to turn a node into a full fledged entity and add said entity to the current game
class s_EntityFactory
{
private:
	const bool isGame;
	pugi::xml_document charPrefab;
	pugi::xml_node charNode;
	//pugi::xml_node playerOldNode;
	Sys& sys;
	std::vector<unsigned int>& entityList;
	std::map<std::string, ReadFunc> readFuncs;

public:
	s_EntityFactory(bool isGame, std::vector<unsigned int>& entityList, Sys& sys);
	~s_EntityFactory();

	void readItems(pugi::xml_node parent, std::vector<unsigned int> IDList, bool isGame);
	pugi::xml_node  findPrefab(std::string name);
	int findInventoyItems(pugi::xml_node items);
	void readLimbSection(const pugi::xml_node& parent, unsigned int parentID);
	void spawnPrefab(const Arguments& args);
	bool spawnPrefab(std::string name, const unsigned int& ID);
	bool spawnPrefabAt(std::string name, const unsigned int& ID, sf::Vector2f loc);
	void saveMap(pugi::xml_node& node, std::vector<unsigned int>& idsToKeepLoaded);
	bool saveEntity(const unsigned int& ID, pugi::xml_node& parent);//returns true if found and saved
	void saveInventories(pugi::xml_node& parent, std::vector<unsigned int>& idsToKeepLoaded);
	void removeEntity(const Arguments& args);
	void removeEntity(const unsigned int& ID);

	void convertPrefab(pugi::xml_node prefab, const unsigned int& ID);

	void f_Name(const unsigned int&, const pugi::xml_node&);
	void f_worldObject(const unsigned int&, const pugi::xml_node&);
	void f_health(const unsigned int&, const pugi::xml_node&);
	void f_damager(const unsigned int&, const pugi::xml_node&);
	void f_physics(const unsigned int&, const pugi::xml_node&);
	void f_action(const unsigned int&, const pugi::xml_node&);
	void f_ai(const unsigned int&, const pugi::xml_node&);
	void f_limb(const unsigned int&, const pugi::xml_node&);
	void f_bodySocket(const unsigned int&, const pugi::xml_node&);
	void f_uigraphics(const unsigned int&, const pugi::xml_node&);
	void f_portal(const unsigned int&, const pugi::xml_node&);
	void f_graphics(const unsigned int&, const pugi::xml_node&);
	void f_inventoryItem(const unsigned int&, const pugi::xml_node&);
	void f_inventory(const unsigned int&, const pugi::xml_node&);
	void f_tileChanger(const unsigned int&, const pugi::xml_node&);
	void f_default(const unsigned int&, const pugi::xml_node&);

};
#endif