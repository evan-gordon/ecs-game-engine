//Evan Gordon

#ifndef S_ACTION_H
#define S_ACTION_H

#include <map>

#include "../pugixml.hpp"

#include "components/c_Action.h"

class s_Action
{
public:
	std::map<unsigned int, c_Action> components;

	~s_Action();

	void update();
	void addComponent(unsigned int ID, c_Action action);
	void removeComponent(unsigned int ID);
	void savetoFile(pugi::xml_node parent);
	c_Action& getAction(unsigned int ID);
	void setAction(unsigned int ID, int lookAngle);
};

#endif