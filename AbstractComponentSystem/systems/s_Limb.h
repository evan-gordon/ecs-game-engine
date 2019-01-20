//Evan Gordon
#ifndef S_LIMB_H
#define S_LIMB_H

#include <map>
#include <memory>

#include <SFML/System.hpp>
#include "../pugixml.hpp"

#include "components/c_Limb.h"
#include "s_LinkedPosition.h"
#include "../services/Locator.h"

class s_Limb
{
public:
	s_Limb(s_LinkedPosition& linkedPositionManager);
	~s_Limb();

	void update();
	void addBodySocket(const unsigned int& ID);
	void saveToFile(const unsigned int& ID, pugi::xml_node& parent);
	void attachTo(unsigned int ID, unsigned int parentID);
	void detach(unsigned int ID);
	t_Limb to_Type(const std::string& str);

	bool exists(const unsigned int& ID);
	c_Limb * find(unsigned int ID);
	std::vector<c_Limb *> getDescendants(c_Limb& c);
	std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> getDescendantLimbs(c_Limb& c);
	std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> getEmptyDescendantLimbs(c_Limb& c);
	void addComponent(unsigned int ID, c_Limb newComponent);
	//void removeComponent(const unsigned int& ID);

	//funcs i need to write tomorrow

	//current problems, when i attach a limb, how do i know which slot it goes into..

	//the id used in items is to be the same as its limbs id
	//the id used in characters is to be the id of the owning character (player/NPC)
	std::map<unsigned int, std::shared_ptr<c_Limb>> items, characters;
private:
	void detachChild(c_Limb &parent, unsigned int ID);//returns removed child

	c_Limb * findInList(unsigned int ID, std::map<unsigned int, std::shared_ptr<c_Limb>>& list);//helper function for reducing size ofhelper func code
	c_Limb * findInDescendants(unsigned int ID, c_Limb& parent);

	s_LinkedPosition& linkedPositionManager;
	std::vector<unsigned int> limbIDList;
	std::map<std::string, t_Limb>limbMap;
};
#endif