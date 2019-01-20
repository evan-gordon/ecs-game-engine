//Evan Gordon
#include "s_Health.h"

s_Health::s_Health(){}

void s_Health::update()
{
	//check for elements with 0 health
	//kill limb
}

const std::map<unsigned int, c_Health>& s_Health::getList(){return components;}


void s_Health::saveToFile(const unsigned int& ID, pugi::xml_node& parent)
{
	pugi::xml_node curr = parent.append_child("health");
	curr.append_child("max");
	curr.append_child("cmax");
	curr.append_child("curr");
	std::string temp = std::to_string(components[ID].MAXHealth);
	curr.child("max").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].currMax);
	curr.child("cmax").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].curr);
	curr.child("curr").append_child(pugi::node_pcdata).set_value(temp.c_str());
}

void s_Health::addComponent(unsigned int ID, c_Health& health){components.insert(std::pair<unsigned int, c_Health>(ID, health));}

void s_Health::removeComponent(const unsigned int& ID){components.erase(ID);}

void s_Health::dealDamage(unsigned int ID, int dmg /*also maybe include ammount to remove, and maybe % sub from curr max*/)
{
	if (components.find(ID) != components.end())
	{
		c_Health& temp = components.at(ID);
		temp.curr += -dmg;
		temp.currMax += -(dmg / 10.0 + 0.5);//for now 1/10th of damage is unhealable
		if (temp.curr < 0){ temp.curr = 0; }
		if (temp.currMax < 0){ temp.currMax = 0; }

		Locator::getConsole().log(std::to_string(ID) + "Health is now: cmax = " + std::to_string(temp.currMax) + " curr = " + std::to_string(temp.curr) + ".");
		return;
	}
	Locator::getConsole().log("Missing ID: " + std::to_string(ID) + " cannot deal damage.");
}

void s_Health::heal(unsigned int ID, int ammount)
{
	if (components.find(ID) != components.end())
	{
		c_Health& temp = components.at(ID);
		temp.curr += ammount;
		if (temp.curr > temp.currMax)//health cand be greater than curr max
		{
			temp.curr = temp.currMax;
		}
		return;
	}
	Locator::getConsole().log("Missing ID: " + std::to_string(ID) + " cannot heal.");
}

s_Health::~s_Health(){}