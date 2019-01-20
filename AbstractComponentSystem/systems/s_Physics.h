//Evan Gordon

#ifndef S_PHYSICS_H
#define S_PHYSICS_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include "components/c_Physics.h"
#include "s_WorldObject.h"
#include "components/c_Action.h"
#include "s_Action.h"
#include "s_Graphics.h"
#include "s_Map.h"

#include <map>
#include <memory>
#include <exception>

class s_Physics//later the physics system class may need to be split up for orginization, or elements in the map will need to be put into different maps
{
public:
	const float acc = 0.1f, friction = 0.1f;
	sf::Time& deltaTime;
	std::map<unsigned int, c_Physics> components;
	s_Map& gameMap;
	s_Graphics& graphicsManager;
	s_WorldObject& worldObjectManager;
	s_Action& inputManager;

	s_Physics(s_WorldObject& wordlObjects, s_Graphics& graphicsManager, s_Action& inputManager, s_Map& gameMap, sf::Time& deltaTime);
	~s_Physics();

	void update();
	void updatePhysics(unsigned int ID, c_Physics& curr, c_Action& action);
	void addComponent(unsigned int, c_Physics newComponent);
	c_Physics& getComponent(unsigned int ID);
	const std::map<unsigned int, c_Physics>& getComponentsMap();
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);
	//broadcast func?
};

#endif