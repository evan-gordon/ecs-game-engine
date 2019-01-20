//Alexander Frisk

#ifndef C_AI_H
#define C_AI_H

#include <string>

#include "Component.h"

class c_AI :public Component
{
public:
	bool moving;
	int time, delay, direction;//direction to be angle to face
	std::string type;

	c_AI();
	c_AI(std::string type, bool moving, int delay);
	~c_AI();

};

#endif