//Evan Gordon
#include "s_Damager.h"

s_Damager::s_Damager(s_WorldObject& worldObjectManager, s_Graphics& graphicsManager, s_Health& healthManager) :
worldObjectManager(worldObjectManager), graphicsManager(graphicsManager), healthManager(healthManager)
{}
//tomorrow todo, 
//write this, add health comp to player. and damager to ai. test and get working
//use lots of log prints
void s_Damager::update(int timeInMili)
{
	auto list = healthManager.getList();//get list of all ids with health
	for (auto it = components.begin(); it != components.end(); it++)//compare with list of all damage dealing ids
	{
		if (it->second.cooldown)//update cooldown for each
		{
			it->second.currTime -= sf::milliseconds(timeInMili);
			if (it->second.currTime <= sf::Time::Zero)
			{
				it->second.currTime = it->second.delayTime;
				it->second.cooldown = false;
			}
		}

		for (auto healthIt = list.begin(); healthIt != list.end(); healthIt++)
		{
			auto topLeftOne = graphicsManager.getUpperLeftPos(it->first);
			auto topLeftTwo = graphicsManager.getUpperLeftPos(healthIt->first);
			if (it->first != healthIt->first && worldObjectManager.checkOverlap(it->first, topLeftOne, healthIt->first, topLeftTwo))//if collision && is not itself
			{
				attack(it->first, healthIt->first);
			}
		}
	}

}

void s_Damager::saveToFile(const unsigned int& ID, pugi::xml_node& parent)
{
	pugi::xml_node curr = parent.append_child("damager");
	curr.append_child("dmg");
	std::string temp = std::to_string(components[ID].dmg);
	curr.child("dmg").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].delayTime.asMilliseconds());
	curr.child("delay").append_child(pugi::node_pcdata).set_value(temp.c_str());
}

void s_Damager::addComponent(unsigned int ID, c_Damager& newComponent)
{
	components.insert(std::pair<unsigned int, c_Damager>(ID, newComponent));
}

void s_Damager::removeComponent(const unsigned int& ID)
{
	components.erase(ID);
}

void s_Damager::attack(unsigned int ID, unsigned int attackedID)
{
	c_Damager& temp = components.at(ID);
	if (!temp.cooldown)
	{
		healthManager.dealDamage(attackedID, temp.dmg);
		temp.cooldown = true;
		temp.currTime = temp.delayTime;
	}
}

s_Damager::~s_Damager(){}