//Evan Gordon 2/21/2016 3:04:58 PM

#include "s_Portal.h"

s_Portal::s_Portal(s_WorldObject& worldObjectManager, s_Map& mapManager, s_Graphics& graphicsManager) :
worldObjectManager(worldObjectManager), mapManager(mapManager), graphicsManager(graphicsManager), IDsToTele(), startupTime(), isStartup(true)
{}

void s_Portal::update()
{
	//add case where portal repulses on game startup for a few seconds
	IDsToTele.clear();
	if (components.size() == 0){ return; }

	if (!isStartup)
	{
		suckUp();
	}
	else
	{
		pushBack();
		startupTime += sf::seconds(0.1f / 60.0f);
		if (startupTime.asSeconds() > .16f){ isStartup = false; }
	}
}

void s_Portal::suckUp()
{
	auto objs = worldObjectManager.sorter.getList();
	//suck up items and send to new location / map
	for (auto it = components.begin(); it != components.end(); it++)//for each portal it could be optimised so it only checks if its on the screen
	{
		for (auto objIt = objs.begin(); objIt != objs.end(); objIt++)
		{
			if (objIt->first != it->first)
			{
				double distFrom = worldObjectManager.findDistance(it->first, objIt->first);
				if ((distFrom / 32.0) <= 1.0)//if its close enough, teleport
				{
					IDsToTele.push_back(std::make_tuple(objIt->first, it->second.mapName, it->second.exitIndexLocation));
					resetStartup();
				}
				else if ((distFrom / 32.0) <= 3.0)//if it's within range, call move towards func
				{
					float tempMaxDistPercent = 1.0f - (float)distFrom / 96.0f;
					int angle = angleBetween(worldObjectManager.getLocationf(objIt->first), worldObjectManager.getLocationf(it->first)) - (int)(42.0f * tempMaxDistPercent);
					sf::Vector2f newx(objIt->second.position.x + calcVectorX(4.0f * tempMaxDistPercent, angle), objIt->second.position.y);
					sf::Vector2f newy(objIt->second.position.x, objIt->second.position.y + calcVectorY(4.0f * tempMaxDistPercent, angle));//4.0f is the current sucking strenght multiplyer, maybe make it a const val later?
					//check if new positions are valid
					auto xResult = mapManager.checkForColision(graphicsManager.components.at(objIt->first).sprite.getOrigin(), newx, objIt->second.dimentions, sf::Vector2f(0, 0));
					auto yResult = mapManager.checkForColision(graphicsManager.components.at(objIt->first).sprite.getOrigin(), newy, objIt->second.dimentions, sf::Vector2f(0, 0));
					worldObjectManager.setPosition(objIt->first, sf::Vector2f(newx.x + xResult.x, newy.y + yResult.y));
				}
			}
		}
	}
}

void s_Portal::pushBack()
{
	auto objs = worldObjectManager.sorter.getList();
	//suck up items and send to new location / map
	for (auto it = components.begin(); it != components.end(); it++)//for each portal it could be optimised so it only checks if its on the screen
	{
		for (auto objIt = objs.begin(); objIt != objs.end(); objIt++)
		{
			if (objIt->first != it->first)
			{
				double distFrom = worldObjectManager.findDistance(it->first, objIt->first);
				if ((distFrom / 32.0) <= 3.0)
				{
					float tempMaxDistPercent = 1.0f - (float)distFrom / 96.0f;
					int angle = angleBetween(worldObjectManager.getLocationf(it->first), worldObjectManager.getLocationf(objIt->first)) + (int)(42.0f * tempMaxDistPercent);
					sf::Vector2f newx(objIt->second.position.x + calcVectorX(4.0f * tempMaxDistPercent, angle), objIt->second.position.y);
					sf::Vector2f newy(objIt->second.position.x, objIt->second.position.y + calcVectorY(4.0f * tempMaxDistPercent, angle));
					//check if new positions are valid
					auto xResult = mapManager.checkForColision(graphicsManager.components.at(objIt->first).sprite.getOrigin(), newx, objIt->second.dimentions, sf::Vector2f(0, 0));
					auto yResult = mapManager.checkForColision(graphicsManager.components.at(objIt->first).sprite.getOrigin(), newy, objIt->second.dimentions, sf::Vector2f(0, 0));
					worldObjectManager.setPosition(objIt->first, sf::Vector2f(newx.x + xResult.x, newy.y + yResult.y));
				}
			}
		}
	}
}


void s_Portal::addComponent(unsigned int ID, c_Portal& portal){components.insert(std::pair<unsigned int, c_Portal>(ID, portal));}

void s_Portal::removeComponent(unsigned int ID){components.erase(ID);}

void s_Portal::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	pugi::xml_node curr = parent.append_child("portal");
	curr.append_child("mapname");
	curr.append_child("x");
	curr.append_child("y");
	curr.child("mapname").append_child(pugi::node_pcdata).set_value(components[ID].mapName.c_str());
	curr.child("x").append_child(pugi::node_pcdata).set_value(std::to_string(components[ID].exitIndexLocation.x).c_str());
	curr.child("y").append_child(pugi::node_pcdata).set_value(std::to_string(components[ID].exitIndexLocation.y).c_str());
}

const std::vector<std::tuple<unsigned int, std::string, sf::Vector2f>>& s_Portal::getTeleIDs(){return IDsToTele;}

void s_Portal::linkPortal(const Arguments& args)
{
	sf::Vector2f temp(args.floats[0], args.floats[1]);
	linkPortal(args.ints[0], args.strings[0], temp);
}

void s_Portal::linkPortal(const unsigned int& ID, const std::string& mName, const sf::Vector2f& linkedPos)
{
	if (components.find(ID) != components.end())
	{
		components[ID].exitIndexLocation.x = linkedPos.x;
		components[ID].exitIndexLocation.y = linkedPos.y;
		components[ID].mapName = mName;
	}
	else
	{
		Locator::getConsole().log("Portal link creation failed with arguments: " + mName + ", " + std::to_string(linkedPos.x) + ", " + std::to_string(linkedPos.y));
	}
}

void s_Portal::resetStartup()
{
	isStartup = true;
	startupTime = sf::seconds(0.0f);
}

s_Portal::~s_Portal(){}