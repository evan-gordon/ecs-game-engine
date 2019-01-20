//Evan Gordon

#ifndef C_COLIDABLE_H
#define C_COLIDABLE_H

#include "Component.h"

class c_Colidable:public Component
{
public:
	bool isColidable;

	c_Colidable();
	~c_Colidable();
};

#endif