//Evan Gordon
//Alexander Frisk

#include "s_TileChanger.h"

s_TileChanger::s_TileChanger(std::string& mapNaF, s_Map& mapManager, s_WorldObject& worldObjectManager):
mapNameAndPath(mapNaF), mapManager(mapManager), worldObjectManager(worldObjectManager)
{}

void s_TileChanger::useBehavior(unsigned int userID, unsigned int itemID)//perhaps add a case later for using a set position instead of the position of current object
{
	if (components.at(itemID).mapFileName == mapNameAndPath)//check to make sure a valid tile is being held
	{
		sf::Vector2i position(worldObjectManager.sorter.find(userID)->positionInTiles);
		components.at(itemID).tile.graphics.sprite.setPosition(position.x * 32.0f, position.y * 32.0f);
		mapManager.changeTile(components.at(itemID).tile, position);
	}
	std::cout<<"changing a tile\n";
}

void s_TileChanger::changeTile(unsigned int ID, pugi::xml_node tile)//might have to change second data to an actual tile obj later
{
	components.at(ID).tile = mapManager.readTile(tile);
	components.at(ID).mapFileName = mapNameAndPath;
}

//ui Player menu is supposed to use this
void s_TileChanger::changeTile(unsigned int ID, c_TileChanger newTile)
{
	components.at(ID) = newTile;
	components.at(ID).mapFileName = mapNameAndPath;
}

//used for reading from file
void s_TileChanger::addComponent(unsigned int ID, pugi::xml_node tile)
{
	components.insert(std::make_pair(ID, c_TileChanger(mapNameAndPath, mapManager.readTile(tile))));
}

void s_TileChanger::removeComponent(unsigned int ID)
{
	components.erase(ID);
}

void s_TileChanger::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	parent.append_child("tilechanger");
	mapManager.saveTile(parent.child("tilechanger"), components.at(ID).tile);
}