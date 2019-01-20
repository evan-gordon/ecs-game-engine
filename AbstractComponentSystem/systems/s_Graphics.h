//Evan Gordon

#ifndef S_GRAPHICS_H
#define S_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <map>
#include <iostream>

#include "../services/Locator.h"
#include "components/c_Graphics.h"
#include "S_WorldObject.h"

class s_Graphics
{
public:
	std::map <std::string, sf::Texture> textures;
	std::shared_ptr<sf::RenderWindow> window;
	sf::View& gameView;
	std::map<unsigned int, c_Graphics> components;
	s_WorldObject& worldObjectManager;
	//will sometimes need an action object
	s_Graphics(s_WorldObject& worldObjects, sf::View& gameView, std::shared_ptr<sf::RenderWindow> window);
	~s_Graphics();

	void update();
	sf::Vector2f getUpperLeftPos(unsigned int ID);
	void addComponent(unsigned int ID, c_Graphics& graphic);
	sf::Texture *s_Graphics::getSprite(std::string name);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);
};

#endif
