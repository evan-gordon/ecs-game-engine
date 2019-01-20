//Evan Gordon
#ifndef SAVEDLOCS_H
#define SAVEDLOCS_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../s_WorldObject.h"
#include "../../console/Arguments.h"
#include "../../services/Locator.h"

struct loc
{
	sf::Vector2f pos;
	std::string mapName;

	loc() :pos(), mapName(""){}
	loc(sf::Vector2f p, std::string mName) : pos(p), mapName(mName)
	{}
};
struct locInTiles
{
	sf::Vector2i pos;
	std::string mapName;

	locInTiles() :pos(), mapName(""){}
	locInTiles(sf::Vector2i p, std::string mName) : pos(p), mapName(mName)
	{}
};

class SavedLocs
{
private:
	std::string& mapName;
	int iSerial, fSerial;
	sf::Vector2i nullLocInTiles; sf::Vector2f nullLoc;//needed so const ref can be returned
	std::map<int, locInTiles> locsInTiles;
	std::map<int, loc> locs;

	s_WorldObject& worldObjectManager;

public:
	SavedLocs(std::string& mapName, s_WorldObject& worldObjectManager) : mapName(mapName), iSerial(0), fSerial(0), nullLoc(0.0f, 0.0f), nullLocInTiles(0, 0), locs(), locsInTiles(), worldObjectManager(worldObjectManager)
	{}

	void saveLoc(const Arguments& args)
	{
		saveLoc((unsigned int)args.ints[0]);
	}
	void saveLoc(const unsigned int& ID)
	{
		fSerial++;
		locs.insert(std::make_pair(fSerial, loc(worldObjectManager.getLocationf(ID), mapName)));//saveloc
		Locator::getConsole().log("Saveloc of ID:" + std::to_string(fSerial) + " created.");
	}

	void saveLocInTiles(const Arguments& args)
	{
		saveLocInTiles((unsigned int)args.ints[0]);
	}
	void saveLocInTiles(const unsigned int& ID)
	{
		iSerial++;
		locsInTiles.insert(std::make_pair(iSerial, locInTiles(worldObjectManager.getLocationi(ID), mapName)));//saveLoc
		Locator::getConsole().log("Saveloc in tiles of ID:" + std::to_string(iSerial) + " created.");
	}

	//id used for these functions is local to the savedlocs class
	//for now, command rerouting wont be implemented, so instead ill print the saved information onto the screen
	void getLoc(const Arguments& args) { getLoc(args.ints[0]); }
	/*const sf::Vector2f&*/void getLoc(int ID)
	{
		if (locs.find(ID) != locs.end())
		{
			loc& temp = locs[ID];
			Locator::getConsole().log("Saveloc " + std::to_string(ID) + ": " + temp.mapName + ", " + std::to_string(temp.pos.x) + ", " + std::to_string(temp.pos.y));
			//return locs[ID].pos;//bad
		}
		//return nullLoc;
	}

	void getLocInTiles(const Arguments& args) { getLoc(args.ints[0]); }
	/*const sf::Vector2i&*/void gettLocInTiles(int ID)
	{
		if (locsInTiles.find(ID) != locsInTiles.end())
		{
			locInTiles& temp = locsInTiles[ID];
			Locator::getConsole().log("Saveloc " + std::to_string(ID) + ": " + temp.mapName + ", " + std::to_string(temp.pos.x) + ", " + std::to_string(temp.pos.y));
			//return locsInTiles[ID].pos;//bad
		}
		//return nullLocInTiles;
	}
};

#endif