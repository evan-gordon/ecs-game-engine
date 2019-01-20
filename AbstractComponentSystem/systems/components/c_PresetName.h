//Evan Gordon

#ifndef C_PRESETNAME_H
#define C_PRESETNAME_H

#include <string>

#include "Component.h"

class c_PresetName:public Component
{
public:
	std::string name;

	c_PresetName();
	c_PresetName(std::string name);
	~c_PresetName();

private:

};

#endif