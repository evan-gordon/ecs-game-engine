//Evan Gordon

#ifndef TILE_H
#define TILE_H

#include "c_Graphics.h"
#include "c_Colidable.h"
#include "c_PresetName.h"

struct Tile
{
	c_PresetName name;
	c_Colidable colidable;
	c_Graphics graphics;

	Tile(){}
	Tile(c_PresetName name, c_Colidable colidable, c_Graphics graphics):
		name(name), colidable(colidable), graphics(graphics)
	{}
};

#endif