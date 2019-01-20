//Evan Gordon

#ifndef C_TILECHANGER_H
#define C_TILECHANGER_H

#include <string>

#include "Component.h"
#include "c_Colidable.h"
#include "c_Graphics.h"
#include "c_PresetName.h"
#include "Tile.h"



class c_TileChanger
{
public:
	Tile tile;
	std::string mapFileName; 

	c_TileChanger();
	c_TileChanger(std::string mapFileName, Tile tile);
	~c_TileChanger();
};

#endif