//Evan Gordon 2/16/2016 12:40:11 PM

#include "s_Name.h"

s_Name::s_Name(){}

void s_Name::update()
{

}

void s_Name::addComponent(unsigned int ID, c_Name name)
{
	components.insert(std::pair<unsigned int, c_Name>(ID, name));
}

void s_Name::removeComponent(unsigned int ID)
{
	components.erase(ID);
}

std::string s_Name::getName(unsigned int ID)
{
	auto it = components.find(ID);

	if(it != components.end())
	{return it->second.name;}
	return "";
}

void s_Name::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	parent.append_child("name");
	parent.child("name").append_child(components[ID].name.c_str());
}

unsigned int s_Name::findByName(std::string name)
{
	for(auto it = components.begin(); it != components.end(); it++)
	{
		if(it->second.name == name)
		{return it->first;}
	}
	return 0;//make 0 a invalid id value
}
s_Name::~s_Name(){}