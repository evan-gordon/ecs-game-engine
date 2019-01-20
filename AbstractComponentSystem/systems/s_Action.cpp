//Evan Gordon

#include "s_Action.h"


void s_Action::update()
{
	//determines which actions can be active at the same time i.e. isJumping + move_Left
}

void s_Action::addComponent(unsigned int ID, c_Action action){components.insert(std::pair<unsigned int, c_Action>(ID, action));}

c_Action& s_Action::getAction(unsigned int ID)//really i should never use this
{
	return components[ID];//this creates an action if it doesnt exist, so should probably change this
}

void s_Action::setAction(unsigned int ID, int lookAngle)
{
	for(auto it = components.begin(); it != components.end(); it++)
	{
		if(it->first == ID)
		{
			it->second.oldAngle = it->second.lookAngle;
			it->second.lookAngle = lookAngle;
			return;
		}
	}
}

void s_Action::removeComponent(unsigned int ID){components.erase(ID);}

void s_Action::savetoFile(pugi::xml_node parent){parent.append_child("action");}

s_Action::~s_Action(){}