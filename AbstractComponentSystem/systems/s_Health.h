//Evan Gordon
#ifndef S_HEALTH_H
#define S_HEALTH_H

#include <map>

#include "components\c_Health.h"
#include "../pugixml.hpp"
#include "../services/Locator.h"

//health components are given to a limb, if a part of a limb takes damage, then the whole limb is what recieves it
class s_Health
{
public:
	s_Health();
	~s_Health();

	void update();
	const std::map<unsigned int, c_Health>& getList();
	void saveToFile(const unsigned int& ID, pugi::xml_node& parent);
	void addComponent(unsigned int ID, c_Health& health);
	void removeComponent(const unsigned int& ID);
	void dealDamage(unsigned int ID, int dmg /*alsomaybe include ammount to remove, and maybe % sub from curr max*/);
	void heal(unsigned int ID, int ammount);

	std::map<unsigned int, c_Health> components;
};

#endif