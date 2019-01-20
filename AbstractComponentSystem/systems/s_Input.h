//Evan Gordon

#ifndef S_INPUT_H
#define S_INPUT_H

#include <iostream>
#include <map>
#include <memory>
#include <exception>

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include "../g_Functions.h"
#include "components/c_Input.h"
#include "components/c_Physics.h"
#include "s_Inventory.h"
#include "s_UIGraphics.h"
#include "s_Action.h"
#include "s_Sounds.h"
#include "../services/Locator.h"

class s_Input
{
public:
	std::shared_ptr<sf::Event> event;
	pugi::xml_document input;
	pugi::xml_node inputReader;
	std::map<std::string, c_Input> components;//string will be input name, read from file
	std::map<unsigned int, c_Physics>& physicsComponents;
	//std::map<unsigned int, c_Action>& actionComponents;
	s_Inventory& inventoryManager;
	s_UIGraphics& UIGraphicsManager;
	s_Action& actionsManager;
	s_Sounds& soundManager;

	s_Input(std::shared_ptr<sf::Event> event, std::map<unsigned int, c_Physics>& physicsComponents, s_Action& actionsManager, 
		s_Inventory& inventoryManager, s_UIGraphics& UIGraphicsManager, s_Sounds& soundManager);
	~s_Input();

	std::string update();
	std::string updateIsKeyPressed();
	void readFromFile();
	void addComponent(std::string name, c_Input& newComponent);
	const std::map<std::string, c_Input>& getComponentsMap();
	//broadcast func for paused and other gamestates or a component that manages gamestate
};

#endif