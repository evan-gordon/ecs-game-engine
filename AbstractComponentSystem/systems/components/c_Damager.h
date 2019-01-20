//Evan Gordon
#ifndef C_DAMAGER_H
#define C_DAMAGER_H

#include <SFML/System.hpp>

#include "Component.h"

class c_Damager :public Component
{
public:
	bool cooldown;
	int dmg;//ammount of damage to deal
	sf::Time delayTime, currTime;
	//later could add damage type, so different damage behaviors could be implemented
	c_Damager::c_Damager(){}
	c_Damager::c_Damager(int dmg, int delay)
	{
		cooldown = false;
		this->dmg = dmg;
		this->delayTime = sf::milliseconds(delay);
		this->currTime = sf::milliseconds(0);

		
	}
	c_Damager::~c_Damager(){}
};

#endif