//Evan Gordon

#ifndef S_TARGETENTITY_H
#define S_TARGETENTITY_H

#include "../pugixml.hpp"
#include "../services/Locator.h"

#include <map>
#include <memory>
#include <iostream>
#include <vector>

//#include "../console/EventLog.h"
//save data struct used for holding some special data related to savign and loading
struct SaveData
{
	unsigned int serial;
	bool isParent;
};
//I decided this class didnt need a component, because if i want this code to be as modular as possible, then I should 
//just have the first component arg be the owner of the link, and the second the one that needs linking to, that way
// if  two objects are linked i can request any data i want from other systems as needed
class s_TargetEntity
{
public:
	unsigned int lowestSerial;
	//EventLog& log;
	const std::vector<unsigned int>& entityList;
	std::vector<std::pair<unsigned int, SaveData>> linksReadFromFile;
	std::vector<std::pair<unsigned int, SaveData>> linksReadToFile;
	std::map<unsigned int, unsigned int> components;

	s_TargetEntity(/*EventLog& log, */const std::vector<unsigned int>& entityList);

	void readFromFile(const unsigned int& ID, pugi::xml_node component);
	void addComponent(const unsigned int& ID, const unsigned int& linkTo);
	void removeComponent(const unsigned int& ID);
	void savetoFile(const unsigned int& ID, pugi::xml_node parent);

	unsigned int serialize();
};

#endif