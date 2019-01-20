//Evan Gordon

#ifndef C_HEALTH_H
#define C_HEALTH_H

#include "Component.h"

class c_Health :public Component
{
public:
	int curr, currMax, MAXHealth;
	c_Health::c_Health(){}
	c_Health::c_Health(int health, int currMax, int MAXHealth)
	{
		this->curr = health;
		this->currMax = currMax;
		this->MAXHealth = MAXHealth;
	}
	c_Health::~c_Health(){}
};

#endif