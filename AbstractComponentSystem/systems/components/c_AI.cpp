//Alexander Frisk

#include "c_AI.h"


c_AI::c_AI() :
	type(""), moving(false), direction(-1), time(0), delay(-1)
{}

c_AI::c_AI(std::string type, bool moving, int delay) :
	type(type), moving(moving), direction(-1), time(0), delay(delay)
{}

c_AI::~c_AI() {}