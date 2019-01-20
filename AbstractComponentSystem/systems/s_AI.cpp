//Alexander Frisk

#include "s_AI.h"


s_AI::s_AI(s_Action& actionManager) :
actionManager(actionManager), rng(rd())
{
	//log.open("log.txt");
}

void s_AI::update(int deltaTime) {

	for (auto it = components.begin(); it != components.end(); it++)
	{
		it->second.time += deltaTime;
		updateMovement(it->first, it->second.type);
	}
}

void s_AI::addComponent(unsigned int ID, std::string type) {

	//log << "\nAdded AI parts for ID " << ID; log.flush();
	components.insert(std::pair<unsigned int, c_AI>(ID, c_AI(type, false, 1000)));
}

void s_AI::removeComponent(const unsigned int& ID)
{
	components.erase(ID);
}

void s_AI::updateMovement(unsigned int ID, std::string type)
{
	if (components[ID].time >= components[ID].delay)
	{
		if (components[ID].moving)
		{
			components[ID].moving = false;
			components[ID].direction = -1;
			actionManager.setAction(ID, -1);
		}
		else {
			components[ID].moving = true;
			std::uniform_int_distribution<int> uni(0, 359);
			components[ID].direction = uni(rng);
			actionManager.setAction(ID, components[ID].direction);
		}
		components[ID].time = 0;
	}
}

void s_AI::saveToFile(const unsigned int& ID, pugi::xml_node& parent)
{
	if (components.find(ID) != components.end())
	{
		parent.append_child("ai");
		parent.child("ai").append_child(std::string(components[ID].type).c_str());
	}
}

s_AI::~s_AI() {}