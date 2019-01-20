//Evan Gordon

#ifndef S_LINKEDPOSITION_H
#define S_LINKEDPOSITION_H

#include "../pugixml.hpp"

#include <map>

#include "components/c_WorldObject.h"
#include "components/c_LinkedPosition.h"
#include "s_TargetEntity.h"
#include "s_WorldObject.h"

class s_LinkedPosition
{
public:
	s_TargetEntity& targetManager;
	s_WorldObject& worldObjectManager;
	std::map<unsigned int, c_LinkedPosition> components;

	s_LinkedPosition(s_WorldObject& manager, s_TargetEntity& targetManager);
	~s_LinkedPosition();

	void update();
	void readFromFile(unsigned int ID, pugi::xml_node component);
	void addComponent(unsigned int name, c_LinkedPosition newComponent);
	void createNewLink(unsigned int parent, unsigned int child, const sf::Vector2f& offset);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);

};

#endif