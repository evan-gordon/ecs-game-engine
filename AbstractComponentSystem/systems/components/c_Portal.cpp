//Evan Gordon 2/21/2016 2:30:25 PM

#include "c_Portal.h"

c_Portal::c_Portal(){}

c_Portal::c_Portal(std::string& mapName, sf::Vector2f& exitIndexLocation):
	mapName(mapName), exitIndexLocation(exitIndexLocation)
{}

c_Portal::~c_Portal(){}