#ifndef LINKEDELEMENT_H
#define LINKEDELEMENT_H

#include <map>
//#include <memory>

#include "../../systems/components/c_Action.h"

class LinkedElement
{
public:
	LinkedElement::LinkedElement() : directions() {}
	virtual LinkedElement::~LinkedElement() 
	{}

	void LinkedElement::setDirection(Direction d, LinkedElement * newD)
	{
		directions[d] = newD;
	}

	LinkedElement*  LinkedElement::getDirection(Direction d)
	{
		if (directions.find(d) == directions.end())
		{
			return nullptr;
		}
		return directions[d];
	}
	void LinkedElement::clearDirection() { directions.clear(); }

private:
	std::map<Direction, LinkedElement *> directions;
};
/*
LinkedElement::LinkedElement()
{
}

LinkedElement::~LinkedElement()
{
}//*/

#endif // !LINKEDELEMENT_H

