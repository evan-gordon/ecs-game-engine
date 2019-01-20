//Evan Gordon	2/21/2016 2:27:28 PM

#ifndef C_PORTAL_H
#define C_PORTAL_H

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <string>
//links location of portal to another location on this or another map
class c_Portal:public Component
{
public:
	c_Portal();
	c_Portal(std::string& mapName, sf::Vector2f& exitIndexLocation);
	~c_Portal();

	std::string mapName;
	sf::Vector2f exitIndexLocation;
private:

};

#endif 