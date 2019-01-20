//Evan Gordon
#include "s_LinkedPosition.h"

s_LinkedPosition::s_LinkedPosition(s_WorldObject& manager, s_TargetEntity& targetManager)
	:worldObjectManager(manager), targetManager(targetManager)
{}

void s_LinkedPosition::update()
{
	for (auto it = components.begin(); it != components.end(); it++)//update position to linked objects position
	{
		if(targetManager.components.find(it->first) != targetManager.components.end())
		{
			sf::Vector2f& temp = worldObjectManager.getLocationf(targetManager.components.find(it->first)->second);
			//test code
			temp.x += it->second.offsetVal.x;
			temp.y += it->second.offsetVal.y;
			//end test
			worldObjectManager.setPosition(it->first, temp);//target isnt initializing
		}
	}
}

void s_LinkedPosition::readFromFile(unsigned int ID, pugi::xml_node component)
{
	bool isOffset = component.child("offset").text().as_bool();
	sf::Vector2f offset(component.child("x").text().as_float(), component.child("y").text().as_float());
	//will need to be more complex later to account for rotation of linked obj
	addComponent(ID, c_LinkedPosition(isOffset, offset));
}

void s_LinkedPosition::addComponent(unsigned int name, c_LinkedPosition newComponent){components.insert(std::make_pair(name, newComponent));}

void s_LinkedPosition::createNewLink(unsigned int parent, unsigned int child, const sf::Vector2f& offset)
{
	bool hasOffset = true;
	if (offset.x == 0.f && offset.y == 0.f){hasOffset = false;}

	addComponent(child, c_LinkedPosition(hasOffset, sf::Vector2f(offset.x, offset.y)));
	targetManager.addComponent(child, parent);
}

void s_LinkedPosition::removeComponent(unsigned int ID){components.erase(ID);}

void s_LinkedPosition::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	//not needed yet?
}

s_LinkedPosition::~s_LinkedPosition() {}