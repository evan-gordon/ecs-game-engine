//Evan Gordon

#ifndef WORLDOBJECT_INSERTIONSORT_H
#define WORLDOBJECT_INSERTIONSORT_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "c_WorldObject.h"

class WorldOject_InsertionSort
{
private:
	std::vector<std::pair<unsigned int, c_WorldObject>> components;

public: 
	WorldOject_InsertionSort();

	c_WorldObject* find(unsigned int ID);
	void sort();
	void addComponent(unsigned int ID, c_WorldObject newComponent);
	void erase(unsigned int ID);
	const std::vector<std::pair<unsigned int, c_WorldObject>>& getList();
};

#endif 