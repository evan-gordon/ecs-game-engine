//Evan Gordon	2/16/2016 12:29:11 PM

#ifndef C_NAME_H
#define C_NAME_H

#include "Component.h"
#include <string>

//Holds a string for the name of the entity, can be requested, compared, and is also used as the main tag when saving the entity
class c_Name:public Component
{
public:
	std::string name;

	c_Name();
	c_Name(std::string name);
	~c_Name();
	};
#endif 