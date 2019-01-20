//Evan Gordon

#ifndef S_UIGRAPHICS_H
#define S_UIGRAPHICS_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "components/c_Graphics.h"
#include "../g_Functions.h"
#include "s_TileChanger.h"
#include "s_Inventory.h"
#include "s_Limb.h"
#include "s_Map.h"
#include "../ui/UIInfo.h"
#include "../ui/UIPlayerMenu.h"
#include "../ui/UIExitMenu.h"
#include "../ui/UIPlayerInventory.h"
#include "../ui/UIConsole.h"
//#include "../console/CManager.h"

class s_UIGraphics
{
public:
	std::string mapNameAndPath;
	std::map <std::string, sf::Texture> textures;

	std::shared_ptr<sf::RenderWindow> window;
	sf::View& UIView;
	s_Map& mapManager;
	s_Limb& limbManager;
	s_TileChanger& tileChangerManager;
	s_Inventory& inventoryManager;
	s_Graphics& graphicsManager;
	std::map<unsigned int, std::vector<std::string>> components;//used for saving
																//will sometimes need an action object
	std::unique_ptr<UIPlayerMenu> wrenchMenu;
	UIExitMenu exitMenu;
	UIInfo infoMenu;
	//UIConsole consoleMenu;
	std::unique_ptr<UIPlayerInventory> playerInventoryMenu;
	s_UIGraphics(std::string& mapNaF, sf::View& UIView, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font, s_Map& mapManager, s_TileChanger& tileChangerManager,
		s_Inventory& inventoryManager, s_Graphics& graphicsManager, s_Limb& limbManager);
	//s_UIGraphics(sf::View& UIView, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font, s_Map& mapManager, 
		//s_TileChanger& tileChangerManager, s_Inventory& inventoryManager, s_Graphics& graphicsManager, CManager& cManager);
	~s_UIGraphics();

	void update();
	bool isMenuOpen();
	void togglePlayerMenu(unsigned int ID);
	void move(unsigned int ID, sf::Vector2i vector);
	void select(unsigned int ID);//need to make map name globally accessable
	void addComponent(unsigned int ID, std::string);
	void removeComponent(unsigned int ID);
	void savetoFile(unsigned int ID, pugi::xml_node parent);

	//std::ofstream log;
};

#endif