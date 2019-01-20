//Evan Gordon

#ifndef C_TARGETENTITY_H
#define C_TARGETENTITY_H

#include "c_WorldObject.h"
#include "Component.h"

//this class is to be used for tracking, or storing the location of a certain object in relation to  the object this class blelongs to
//i.e. if say an animal wants to follow the player it will use this class to reffer to the players location
class c_TargetEntity:public Component
{
public:
	bool isLinked;
	c_WorldObject* target;

	c_TargetEntity();
	c_TargetEntity(c_WorldObject& target);
	~c_TargetEntity();
};

#endif