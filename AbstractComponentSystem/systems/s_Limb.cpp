//Evan Gordon
#include "s_Limb.h"

s_Limb::s_Limb(s_LinkedPosition& linkedPositionManager):
linkedPositionManager(linkedPositionManager)
{
	limbMap.insert(std::make_pair("HEAD", HEAD));
	limbMap.insert(std::make_pair("BODY", BODY));
	limbMap.insert(std::make_pair("LEFTARM", LEFTARM));
	limbMap.insert(std::make_pair("RIGHTARM", RIGHTARM));
	limbMap.insert(std::make_pair("LEFTLEG", LEFTLEG));
	limbMap.insert(std::make_pair("RIGHTLEG", RIGHTLEG));
	limbMap.insert(std::make_pair("SECTION", SECTION));

	//try adding to a character (spirit form to inhabiting body)
	//also create ui for visualizing a limb
}

//return true if there is a limb/section with given id
bool s_Limb::exists(const unsigned int& ID)
{
	for each (auto id in limbIDList)
	{
		if (id == ID)
		{
			return true;
		}
	}
	return false;
}

//search all items, and characters, and their descendants for a limb by id
c_Limb * s_Limb::find(unsigned int ID)
{
	auto r = findInList(ID, items);
	if (r != NULL){return r;}

	return findInList(ID, characters);
}

//search given list, and descendants of items in list for id, return NULL if not found
c_Limb * s_Limb::findInList(unsigned int ID, std::map<unsigned int, std::shared_ptr<c_Limb>>& list)
{
	for (auto it = list.begin(); it != list.end(); it++)
	{
		if (it->second->id == ID){return it->second.get();}

		auto r = findInDescendants(ID, *(it->second));
		if (r != NULL){	return r;}
	}
	return NULL;
}

//search descendants of given idem for passed id, if not found return NULL
c_Limb * s_Limb::findInDescendants(unsigned int ID, c_Limb& parent)
{
	auto desc = getDescendants(parent);
	for (auto it = desc.begin(); it != desc.end(); it++)
	{
		if ((*it)->id == ID)
		{
			return *it;
		}
	}
	return NULL;
}

std::vector<c_Limb *> s_Limb::getDescendants(c_Limb& c)
{
	std::vector<c_Limb *> result;
	for (auto it = c.children.begin(); it != c.children.end(); it++)
	{
		if (std::get<2>(*it) != NULL)
		{
			result.push_back(std::get<2>(*it).get());
			auto desc = getDescendants(*std::get<2>(*it));//recurse
			for (auto childIt = desc.begin(); childIt != desc.end(); it++)//add in results
			{
				result.push_back(*childIt);
			}
		}
	}
	return result;
}

//get all limbs that are descendant off of passed limb
std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> s_Limb::getDescendantLimbs(c_Limb& c)
{
	std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> result;
	for (auto it = c.children.begin(); it != c.children.end(); it++)
	{
		if (std::get<2>(*it) != NULL)//dont do anything w empty limbs
		{
			if (std::get<0>(*it) == SECTION)//recurse if is a secton
			{
				auto desc = getDescendantLimbs(*std::get<2>(*it));//recurse
				for (int i = 0; i < desc.size(); ++i)//add in results
				{
					result.push_back(desc[i]);
				}
			}
			else//is another limb, 
			{
				result.push_back(&(*it));
			}
		}
	}
	return result;
}

std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> s_Limb::getEmptyDescendantLimbs(c_Limb& c)
{
	std::vector<std::tuple<t_Limb, sf::Vector2f, std::shared_ptr<c_Limb>> *> result;
	for (auto it = c.children.begin(); it != c.children.end(); it++)
	{
		if (std::get<0>(*it) == SECTION && std::get<2>(*it) != NULL)//recurse if is a secton
		{
			auto desc = getEmptyDescendantLimbs(*std::get<2>(*it));//recurse
			for (int i = 0; i < desc.size(); ++i)
			{
				result.push_back(desc[i]);
			}
		}
		else if (std::get<2>(*it) == NULL)//is an empty limb
		{
			result.push_back(&(*it));
		}
	}
	return result;
}

//remove ID limb from parent, only works on immidiate descendant limb
void s_Limb::detachChild(c_Limb &parent, unsigned int ID)
{
	auto childLimbs = getDescendantLimbs(parent);
	for (auto it = childLimbs.begin(); it != childLimbs.end(); ++it)
	{
		if (std::get<2>(*(*it))->id == ID)//child id was found
		{
			linkedPositionManager.removeComponent(ID);//remove linked position component
			std::get<2>(*(*it))->parent = NULL;
			items.insert(std::make_pair(std::get<2>(*(*it))->id, std::move(std::get<2>(*(*it)))));
			std::get<2>(*(*it)) = NULL;
			return;
		}
	}
}

void s_Limb::attachTo(unsigned int ID, unsigned int parentID)
{
	auto child = items.find(ID);//find and get ref to ID item - make sure to check descendants
	if (child == items.end())
	{
		Locator::getConsole().log("Failed to create attachment, couldnt find child id " + std::to_string(ID));
		return;
	}
	auto parent = find(parentID);
	if (parent == NULL)
	{
		Locator::getConsole().log("Failed to create attachment, couldnt find parent id " + std::to_string(ID));
		return;
	}//finished finding  associated limbs

	//for right now, i dont have a way to select which socket limb goes into
		//for now if socket is same type as limb, insert
	auto emptyNodes = getEmptyDescendantLimbs(*parent);//TODO all results are NULL return a pair vector with type as first arg===========
	for (auto socs = emptyNodes.begin(); socs != emptyNodes.end(); ++socs)
	{
		if (child->second->type == std::get<0>(*(*socs)))//found correct empty socket
		{
			//there are some minor nuances with std::move, i might need to make a move constructor - keep this in mind if bugs show up
			child->second->parent = parent;
			std::get<2>(*(*socs)) = std::move(child->second);//move and attach
			items.erase(child);//since child is now attached remove from items
			linkedPositionManager.createNewLink(parentID, ID, sf::Vector2f(std::get<1>(*(*socs)).x, std::get<1>(*(*socs)).y));
			Locator::getConsole().log("Limb sucessfully attached.");
			return;//found and attached
		}
	}
	Locator::getConsole().log("Unable to find empty socket of type " + std::to_string(child->second->type));
}

//searches items and then characters and detaches a limb if attached
void s_Limb::detach(unsigned int ID)
{
	for (auto it = items.begin(); it != items.end(); it++)
	{
		auto r = findInDescendants(ID, *it->second);
		if (r != NULL)
		{
			detachChild(*(r->parent), ID);
			return;
		}
	}
	auto r = findInList(ID, characters);
	if (r != NULL)
	{
		detachChild(*(r->parent), ID);
		return;
	}
}

//TODO
void s_Limb::update()
{
	//int x = 2;
}

void s_Limb::addBodySocket(const unsigned int& ID)
{
	characters.insert(std::make_pair(ID, std::shared_ptr<c_Limb>()));
}

t_Limb s_Limb::to_Type(const std::string& str)
{
	if (limbMap.find(str) != limbMap.end())
	{
		return limbMap[str];
	}
	else
	{
		return NIL;//default
	}
}

//TODO
void s_Limb::saveToFile(const unsigned int& ID, pugi::xml_node& parent)
{
	pugi::xml_node curr = parent.append_child("limb");
	//TODO
}

void s_Limb::addComponent(unsigned int ID, c_Limb newComponent)
{
	auto it = items.insert(std::make_pair(ID, std::make_shared<c_Limb>(std::move(newComponent))));
	limbIDList.push_back(it.first->first);
}

/*void s_Limb::removeComponent(const unsigned int& ID)
{
	//remove from limbIDList
	components.erase(ID);
}//*/

s_Limb::~s_Limb(){}