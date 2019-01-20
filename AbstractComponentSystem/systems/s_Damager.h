//Evan Gordon
#ifndef S_DAMAGER_H
#define S_DAMAGER_H

#include <map>

#include <SFML/System.hpp>
#include "../pugixml.hpp"

#include "s_WorldObject.h"
#include "s_Health.h"
#include "components\c_Damager.h"
#include "../services/Locator.h"
#include "../g_Functions.h"
#include "s_Graphics.h"

//damager components deal damage to health components
class s_Damager
{
public:
	s_Damager(s_WorldObject& worldObjectManager, s_Graphics& graphicsManager, s_Health& healthManager);
	~s_Damager();

	void update(int timeInMili);
	void saveToFile(const unsigned int& ID, pugi::xml_node& parent);
	void addComponent(unsigned int ID, c_Damager& newComponent);
	void removeComponent(const unsigned int& ID);
	void attack(unsigned int ID, unsigned int attackedID);

	s_WorldObject& worldObjectManager;
	s_Graphics& graphicsManager;
	s_Health& healthManager;
	std::map<unsigned int, c_Damager> components;
};

#endif