//Evan Gordon

#include "s_TargetEntity.h"

s_TargetEntity::s_TargetEntity(/*EventLog& log, */const std::vector<unsigned int>& entityList) :
lowestSerial(1),/* log(log),*/ entityList(entityList)
{}

void s_TargetEntity::readFromFile(const unsigned int& ID, pugi::xml_node component)
{
	bool exists = false;
	for (auto it = linksReadFromFile.begin(); it != linksReadFromFile.end(); it++)//see if serial number is in readfromfile list
	{
		if (it->second.serial == component.text().as_int())//if it is create component,
		{
			exists = true;
			if (it->second.isParent)
			{
				addComponent(it->first, ID);
			}
			else
			{
				addComponent(ID, it->first);
			}
			break;
		}
	}
	if (!exists)//otherwise add to read from file list
	{
		SaveData temp;
		temp.serial = component.text().as_int();
		if (component.first_child().name() == "parent")
		{
			temp.isParent = true;
			linksReadFromFile.push_back(std::pair<unsigned int, SaveData>(ID, temp));
		}
		else
		{
			temp.isParent = false;
			linksReadFromFile.push_back(std::pair<unsigned int, SaveData>(ID, temp));
		}
	}
}

//if both ids exist add the pair to the components map
void s_TargetEntity::addComponent(const unsigned int& ID, const unsigned int& linkTo)
{
	//if both id's exist create link
	if (std::find(entityList.begin(), entityList.end(), ID) != entityList.end() && std::find(entityList.begin(), entityList.end(), linkTo) != entityList.end())
	{
	components.insert(std::make_pair(ID, linkTo));
	}
	else
	{
		Locator::getConsole().log("Error in Target entity; link from " + std::to_string(ID) + " to " + std::to_string(linkTo) + " not created.");
	}
}

void s_TargetEntity::removeComponent(const unsigned int& ID)
{
	components.erase(ID);
}

void s_TargetEntity::savetoFile(const unsigned int& ID, pugi::xml_node parent)
{
	pugi::xml_node curr;
	std::vector<std::pair<unsigned int, SaveData>>::iterator linkIt;
	for (linkIt = linksReadToFile.begin(); linkIt != linksReadToFile.end(); linkIt++)
	{
		if (linkIt->first == ID)//see if one of the two in that pair was already saved
		{
			curr = parent.append_child("targetentity");
			curr.text().set(std::to_string(linkIt->second.serial).c_str());
			if (linkIt->second.isParent)
			{
				curr.append_child("parent");
			}
			else
			{
				curr.append_child("child");
			}
			linksReadToFile.erase(linkIt);
			return;
		}
	}
	//in this case neither of the two in this link have yet to be read to file, if they exist
	if(components.find(ID) != components.end())//found parent id in components
	{
		curr = parent.append_child("targetentity");
		SaveData temp;
		temp.serial = serialize();
		temp.isParent = false;
		curr.set_value(std::to_string(temp.serial).c_str());
		curr.append_child("parent");
		linksReadToFile.push_back(std::pair<unsigned int, SaveData>(components.find(ID)->second, temp));
		components.erase(ID);
	}
	else
	{
		for (auto it = components.begin(); it != components.end(); it++)//look for it being child link
		{
			if (it->second == ID)//if found, save and remove
			{
				curr = parent.append_child("targetentity");
				SaveData temp;
				temp.serial = serialize();
				temp.isParent = true;
				curr.set_value(std::to_string(temp.serial).c_str());
				curr.append_child("child");
				linksReadToFile.push_back(std::pair<unsigned int, SaveData>(components.find(ID)->first, temp));
				it = components.erase(it);
				break;
			}
		}
	}
}

//just creates simple serial number used for saving
unsigned int s_TargetEntity::serialize()
{
	unsigned int temp = lowestSerial;
	lowestSerial++;
	return temp;
}