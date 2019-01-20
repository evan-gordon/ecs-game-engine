//Evan Gordon	2/16/2016 12:34:49 PM

#ifndef S_NAME_H
#define S_NAME_H

#include <map>

#include "../pugixml.hpp"

#include "components/c_Name.h"

//this system manages the names for all entities in the game
class s_Name
{
public:
	std::map<unsigned int, c_Name> components;

	s_Name();
	~s_Name();

	void update();
	void addComponent(unsigned int ID, c_Name name);
	void removeComponent(unsigned int ID);
	std::string getName(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);
	unsigned int findByName(std::string name);
private:

};

#endif 