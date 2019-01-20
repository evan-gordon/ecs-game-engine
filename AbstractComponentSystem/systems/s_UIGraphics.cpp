//Evan Gordon
//Alexander Frisk

#include "s_UIGraphics.h"

s_UIGraphics::s_UIGraphics(std::string& mapNaF, sf::View& UIView, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font, s_Map& mapManager, s_TileChanger& tileChangerManager,
	s_Inventory& inventoryManager, s_Graphics& graphicsManager, s_Limb& limbManager) :
	mapNameAndPath(mapNaF), infoMenu(font), UIView(UIView), window(window), mapManager(mapManager), tileChangerManager(tileChangerManager), inventoryManager(inventoryManager), 
		graphicsManager(graphicsManager), limbManager(limbManager)
{
	textures.insert(std::make_pair("images/mapMakerMenu.png", sf::Texture()));
	if (!textures["images/mapMakerMenu.png"].loadFromFile("images/mapMakerMenu.png"))
	{throw(42);}

	textures.insert(std::make_pair("images/playerInventory.png", sf::Texture()));
	if (!textures["images/playerInventory.png"].loadFromFile("images/playerInventory.png"))
	{throw(42);}

	exitMenu = UIExitMenu(font, textures.at("images/mapMakerMenu.png"), sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));
	exitMenu.toggle();
}

void s_UIGraphics::update()
{
	if(wrenchMenu != NULL && wrenchMenu->getCanDraw()){wrenchMenu->update();}//this might throw an error later when more ui's are added

	if(playerInventoryMenu != NULL && playerInventoryMenu->getCanDraw()){playerInventoryMenu->update();}

	window->setView(UIView);
	
	for (auto it = components.begin(); it != components.end(); it++)
	{
		for (auto uiIT = it->second.begin(); uiIT != it->second.end(); uiIT++)
		{
			if (*uiIT == "wrenchmenu" && wrenchMenu->getCanDraw()){wrenchMenu->draw(*window);}

			if (*uiIT == "playerinventory" && playerInventoryMenu->getCanDraw()){playerInventoryMenu->draw(*window);}
		}
	}

	infoMenu.update();
	if (infoMenu.getCanDraw())
	{infoMenu.draw(*window);}
	if(Locator::getConsoleUI().getCanDraw())
	{Locator::getConsoleUI().draw(*window);}
	if(exitMenu.getCanDraw())
	{exitMenu.draw(*window);}
}

void s_UIGraphics::togglePlayerMenu(unsigned int ID)//may need to change this functionality later, if more weaponmenus are added
{
	if (components.find(ID) != components.end())
	{
		//if (components[ID][0] == "wrenchmenu")
		for (auto it = components[ID].begin(); it != components[ID].end(); it++)
		{
			if (*it == "wrenchmenu")
			{
				wrenchMenu->toggle();
				return;
			}
		}
	}
}

void s_UIGraphics::move(unsigned int ID, sf::Vector2i vector)
{
	if (components.find(ID) != components.end())
	{
		for (auto it = components[ID].begin(); it != components[ID].end(); it++)
		{
			if (*it == "wrenchmenu" && wrenchMenu->getCanDraw())
			{
				wrenchMenu->moveActiveItem(vector);
				return;
			}
			if (*it == "playerinventory" && playerInventoryMenu->getCanDraw())
			{
				playerInventoryMenu->moveActiveItem(vector);
				return;
			}
		}
	}
}

void s_UIGraphics::select(unsigned int ID)
{
	c_TileChanger temp;
	if (components.find(ID) != components.end())
	{
		for (auto it = components[ID].begin(); it != components[ID].end(); it++)
		{
			if (*it == "wrenchmenu" && wrenchMenu->getCanDraw())
			{
				temp = wrenchMenu->setActiveItem(mapNameAndPath);
				tileChangerManager.changeTile(ID, temp);
				wrenchMenu->toggle();
				return;
			}
			else if (*it == "playerinventory"  && playerInventoryMenu->getCanDraw())
			{
				playerInventoryMenu->select();
				return;
			}
		}
		wrenchMenu->setActiveItem(mapNameAndPath);
	}
}

bool s_UIGraphics::isMenuOpen()
{
	if(wrenchMenu != NULL && wrenchMenu->getCanDraw())//add case for all UI's that are added
	{return true;}
	else if(exitMenu.getCanDraw())
	{return true;}
	else if(Locator::getConsoleUI().getState() == CONSOLE)
	{return true;}
	else if(playerInventoryMenu != NULL && playerInventoryMenu->getCanDraw())
	{return true;}
	return false;
}

void s_UIGraphics::addComponent(unsigned int ID, std::string UIType)
{
	if (components.find(ID) == components.end())//if it doesnt exist yet create component (entities can have more than one associated ui, hence the vector)
	{
		components.insert(std::pair<unsigned int, std::vector<std::string>>(ID, std::vector<std::string >()));
	}
	components.at(ID).push_back(UIType);//add ui type to component

	if (UIType == "wrenchmenu")
	{
		wrenchMenu = util::make_unique<UIPlayerMenu>(ID, true, textures.at("images/mapMakerMenu.png"), mapManager);
		wrenchMenu->setPosition(1132.0, 0.0);
		wrenchMenu->toggle();
	}
	if (UIType == "playerinventory")
	{
		playerInventoryMenu = util::make_unique<UIPlayerInventory>(true, textures.at("images/playerInventory.png"), inventoryManager, graphicsManager, limbManager);
		playerInventoryMenu->setPosition(1132.0, 0.0);
		playerInventoryMenu->toggle();
	}

}

void s_UIGraphics::removeComponent(unsigned int ID)
{
	components.erase(ID);
}

void s_UIGraphics::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	parent.append_child("uigraphics");
	for (auto uiIT = components[ID].begin(); uiIT != components[ID].end(); uiIT++)
	{
		parent.child("uigraphics").append_child((*uiIT).c_str());
	}
}

s_UIGraphics::~s_UIGraphics() {}