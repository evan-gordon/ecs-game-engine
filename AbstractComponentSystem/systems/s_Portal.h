//Evan Gordon	2/21/2016 3:00:19 PM

#ifndef S_PORTAL_H
#define S_PORTAL_H

#include <map>
#include <vector>
#include <tuple>

#include "../pugixml.hpp"

#include "s_Map.h"
#include "s_WorldObject.h"
#include "s_Graphics.h"
#include "components/c_portal.h"
#include "../g_Functions.h"
#include "../console/Arguments.h"
#include "../services/Locator.h"

//Portal class, manages all portals to other maps
//will be able to suck up items that are within the range into it and add them to map portal is connected to
//will also be able to suck up people in the game, or just the player?
class s_Portal
{
public:
	std::map<unsigned int, c_Portal> components;
	s_WorldObject&  worldObjectManager;
	s_Map& mapManager;
	s_Graphics& graphicsManager;
	std::vector<std::tuple<unsigned int, std::string, sf::Vector2f>> IDsToTele;// id, mName, pos to put at

	s_Portal(s_WorldObject& worldObjcetManager, s_Map& mapManager, s_Graphics& graphicsManager);
	~s_Portal();

	void update();
	void resetStartup();
	void suckUp();
	void pushBack();
	void addComponent(unsigned int ID, c_Portal& graphic);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);

	const std::vector<std::tuple<unsigned int, std::string, sf::Vector2f>>& getTeleIDs();
	void linkPortal(const Arguments& args);
	void linkPortal(const unsigned int&, const std::string& mName, const sf::Vector2f& linkedPos);
private:
	bool isStartup;
	sf::Time startupTime;

};

#endif 