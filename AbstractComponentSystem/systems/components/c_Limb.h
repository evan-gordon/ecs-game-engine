//Evan Gordon
#ifndef C_LIMB_H
#define C_LIMB_H

#include "../../g_Functions.h"

#include <SFML/System.hpp>

#include <memory>
#include <vector>
//nil is in here to keep any of these from being equal to NULL for some reason
enum t_Limb{NIL = 0, HEAD, BODY, LEFTARM, RIGHTARM, LEFTLEG, RIGHTLEG, SECTION};//section is for each image in a limb
//typedef std::pair<sf::Vector2f, std::shared_ptr<c_Limb>> Node;
//a limb is an imaginary wrapper over the parts of a limb
struct c_Limb
{
	unsigned int id;//limb itself's id if type is limb
	t_Limb type;
	c_Limb * parent;
	std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>>> children;
	//std::vector<std::unique_ptr<Joint>> images;

	//a limb needs to know what sockets, and socket types it has, but doesnt need the actual contents
	//at creaton
	//ammound of children are to be fixed
	c_Limb::c_Limb(unsigned int ID, t_Limb type, std::vector<std::pair<t_Limb, sf::Vector2f>> c) :
		id(ID), type(type), parent(NULL)
	{
		for (auto it = c.begin(); it != c.end(); it++)
		{
			children.push_back(std::tuple<t_Limb, sf::Vector2f,
				std::shared_ptr<c_Limb >> (it->first, it->second, NULL));
		}
	}
	c_Limb::c_Limb(unsigned int ID, t_Limb type, c_Limb * parent, std::vector<std::pair<t_Limb, sf::Vector2f>> c) :
		id(ID), type(type),  parent(parent)
	{
		for (auto it = c.begin(); it != c.end(); it++)
		{
			children.push_back(std::tuple<t_Limb, sf::Vector2f, 
				std::shared_ptr<c_Limb>>(it->first, it->second, NULL));
		}
	}
	c_Limb::~c_Limb(){ parent = NULL; }
};
#endif