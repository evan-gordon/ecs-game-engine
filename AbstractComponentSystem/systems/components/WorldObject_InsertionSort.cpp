//Evan Gordon

#include "WorldObject_InsertionSort.h"

WorldOject_InsertionSort::WorldOject_InsertionSort()
{}

c_WorldObject* WorldOject_InsertionSort::find(unsigned int ID)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		if(components[i].first == ID)
		{return &components[i].second;}
	}

	return NULL;
}

void WorldOject_InsertionSort::sort()
{
	if(components.size() <= 1) {return;}
	for(unsigned int curr = 1; curr < components.size(); curr++)// why start at one, if its by ids, shoudlnt it go to size + 1 then
	{
		auto currData = components[curr];
		int prev = curr - 1;
		//position is going to be located at the origin, need to subtract origin from it, and add height
		while(prev >= 0 && components[prev].second.position.y > currData.second.position.y)//add always draw on bottom case?, and also case for linked items
		{
			components[prev + 1] = components[prev];
			prev = prev - 1;
		}
		components[prev + 1] = currData;
	}
}

void WorldOject_InsertionSort::addComponent(unsigned int ID, c_WorldObject newComponent)
{
	components.push_back(std::make_pair(ID, newComponent));
	sort();
}

void WorldOject_InsertionSort::erase(unsigned int ID)
{
	for(auto it = components.begin(); it != components.end(); it++)
	{
		if(it->first == ID)
		{
			components.erase(it);
			return; 
		}
	}
}

const std::vector<std::pair<unsigned int, c_WorldObject>>& WorldOject_InsertionSort::getList(){return  components;}