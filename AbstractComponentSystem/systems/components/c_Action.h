//Evan Gordon

#ifndef C_ACTION_H
#define C_ACTION_H

#include "Component.h"

enum Direction{NONE, UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
class c_Action:public Component
{
public:
	//bool move_Left, move_Right, move_Up, move_Down;
	int lookAngle, oldAngle;
	c_Action();
	~c_Action();
};

#endif