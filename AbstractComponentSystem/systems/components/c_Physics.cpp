//Evan Gordon

#include "c_Physics.h"

c_Physics::c_Physics(){}

c_Physics::c_Physics(float maxVelocity)
	:velocity(0.0f, 0.0f), acc(0.0f, 0.0f), maxVelocity(maxVelocity), maxAcc(maxVelocity), appliedForce(false)
{}

c_Physics::~c_Physics() {}