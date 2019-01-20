//Evan Gordon

#ifndef C_PHYSICS_H
#define C_PHYSICS_H

#include <SFML/Graphics.hpp>
#include "c_WorldObject.h"
#include "Component.h"

class c_Physics:public Component
{
public:
	bool appliedForce;
	float maxVelocity, maxAcc;
	sf::Vector2f velocity, acc;

	c_Physics();
	c_Physics(float maxVelocity);
	~c_Physics();
};

#endif