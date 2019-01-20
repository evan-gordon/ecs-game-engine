//Evan Gordon

#include "s_WorldObject.h"

void s_WorldObject::setPosition(unsigned int ID, sf::Vector2i pos)
{
	c_WorldObject* temp = sorter.find(ID);
	if(temp != NULL)
	{
		temp->positionInTiles = pos;
		temp->position.x = (float)pos.x * 32.0f;
		temp->position.y = (float)pos.y * 32.0f;
	}
}

void s_WorldObject::setPosition(unsigned int ID, sf::Vector2f pos)
{
	c_WorldObject* temp = sorter.find(ID);
	if(temp != NULL)
	{
		temp->position = pos;
		temp->positionInTiles.x = (int)(pos.x / 32.0);
		temp->positionInTiles.y = (int)(pos.y / 32.0);
	}
}

void s_WorldObject::update(){sorter.sort();}

void s_WorldObject::move(unsigned int ID, sf::Vector2i pos)
{
	c_WorldObject* temp = sorter.find(ID);
	if(temp != NULL)
	{
		temp->positionInTiles += pos;
		temp->positionInTiles.x = (int)(temp->position.x / 32.0);
		temp->positionInTiles.y = (int)(temp->position.y / 32.0);
	}
}

void s_WorldObject::move(unsigned int ID, sf::Vector2f pos)
{
	c_WorldObject* temp = sorter.find(ID);
	if(temp != NULL)
	{
		//Use (int) instead of round and we never talk about this anymore
		temp->position += pos;
		temp->positionInTiles.x = (int)(temp->position.x / 32.0);
		temp->positionInTiles.y = (int)(temp->position.y / 32.0);
	}
}



void s_WorldObject::addComponent(unsigned int name, c_WorldObject newComponent){sorter.addComponent(name, newComponent);}

double s_WorldObject::findDistance(unsigned int first, unsigned int second)//returns dist between 2 objs, 
{
	sf::Vector2f firstPos = sorter.find(first)->position;
	sf::Vector2f secondPos = sorter.find(second)->position;

	float result = ((firstPos.y - secondPos.y) * (firstPos.y - secondPos.y)) + ((firstPos.x - secondPos.x) * (firstPos.x - secondPos.x));
	if(result < 0){result = -result;}

	return sqrt(result);
}

bool s_WorldObject::checkOverlap(unsigned int first, const sf::Vector2f& topLeftOne, unsigned int second, const sf::Vector2f& topLeftTwo)
{
	auto f = sorter.find(first);
	auto s = sorter.find(second);
	//get center for each, 
	sf::Vector2f fhalfWidth(f->dimentions.x / 2.0f, f->dimentions.y / 2.0f);//calc dimensions for each
	sf::Vector2f shalfWidth(s->dimentions.x / 2.0f, s->dimentions.y / 2.0f);
	//hand to ddetect collision func
	return checkCollision(sf::Vector2f(topLeftOne.x + fhalfWidth.x, topLeftOne.y + fhalfWidth.y), fhalfWidth, sf::Vector2f(topLeftTwo.x + shalfWidth.x, topLeftTwo.y + shalfWidth.y), shalfWidth);
}

void s_WorldObject::moveTowards(unsigned int first, unsigned int second, float speed)//maybe get teh speed from physics later?
{
	//move first position towards second
	auto currHypotenuse = findDistance(first, second);
	if(currHypotenuse <= (double)speed)//case for if new position would be past obj
	{setPosition(first, sorter.find(second)->position); return;}

	sf::Vector2f newPosition;
	newPosition.x = (float)(((sorter.find(second)->position.x - sorter.find(first)->position.x) / currHypotenuse) * speed);
	newPosition.y = (float)(((sorter.find(second)->position.y - sorter.find(first)->position.y) / currHypotenuse) * speed);

	move(first, newPosition);//move the element to be moved, by the disances stored in newPosition	
}

sf::Vector2f s_WorldObject::getLocationf(const unsigned int& ID)//if item does not exist NULL will be returned
{
	auto found = sorter.find(ID);
	if(found != NULL)
	{
		return found->position;
	}
	return sf::Vector2f(-64.0f, -64.0f);
}

sf::Vector2i s_WorldObject::getLocationi(const unsigned int& ID)
{
	auto found = sorter.find(ID);
	if (found != NULL)
	{
		return found->positionInTiles;
	}
	return sf::Vector2i(-2, -2);
}

void s_WorldObject::removeComponent(unsigned int ID){sorter.erase(ID);}

void s_WorldObject::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	auto curr = parent.append_child("worldobject");
	c_WorldObject worldObj = *sorter.find(ID);
	if(worldObj.positionAsFloat)
	{
		std::string temp = std::to_string(worldObj.positionAsFloat);
		curr.append_child("asfloat");
		curr.child("asfloat").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.position.x);
		curr.append_child("x");
		curr.child("x").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.position.y);
		curr.append_child("y");
		curr.child("y").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.dimentions.x);
		curr.append_child("width");
		curr.child("width").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.dimentions.y);
		curr.append_child("height");
		curr.child("height").append_child(pugi::node_pcdata).set_value(temp.c_str());
	}
	else //save as int
	{
		std::string temp = std::to_string(worldObj.positionAsFloat);
		curr.append_child("asfloat");
		curr.child("asfloat").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.positionInTiles.x);
		curr.append_child("x");
		curr.child("x").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.positionInTiles.y);
		curr.append_child("y");
		curr.child("y").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.dimentions.x);
		curr.append_child("width");
		curr.child("width").append_child(pugi::node_pcdata).set_value(temp.c_str());
		temp = std::to_string(worldObj.dimentions.y);
		curr.append_child("height");
		curr.child("height").append_child(pugi::node_pcdata).set_value(temp.c_str());
	}
}

s_WorldObject::~s_WorldObject(){}