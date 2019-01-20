//Evan Gordon

#ifndef s_WORLDOBJECT_H
#define s_WORLDOBJECT_H

#include "components/c_WorldObject.h"
#include "components/WorldObject_InsertionSort.h"

#include <map>
#include <memory>
#include <string>
#include <cmath>

#include "../pugixml.hpp"
#include "../g_Functions.h"

class s_WorldObject
{
public:
	WorldOject_InsertionSort sorter;

	~s_WorldObject();

	void update();
	void setPosition(unsigned int ID, sf::Vector2i pos);
	void setPosition(unsigned int ID, sf::Vector2f pos);
	void move(unsigned int ID, sf::Vector2i pos);
	void move(unsigned int ID, sf::Vector2f pos);
	void addComponent(unsigned int name, c_WorldObject newComponent);
	double findDistance(unsigned int first, unsigned int second);//returns dist between 2 objs, 
	bool checkOverlap(unsigned int first, const sf::Vector2f& topLeftOne, unsigned int second, const sf::Vector2f& topLeftTwo);
	void moveTowards(unsigned int first, unsigned int second, float speed);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);

	sf::Vector2f getLocationf(const unsigned int& ID);
	sf::Vector2i getLocationi(const unsigned int& ID);
};

#endif