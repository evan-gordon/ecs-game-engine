//Evan Gordon
#ifndef SYS_H
#define SYS_H

#include <memory>
#include <string>

#include "s_WorldObject.h"
#include "s_Health.h"
#include "s_Damager.h"
#include "s_Physics.h"
#include "s_Input.h"
#include "s_AI.h"
#include "s_Action.h"
#include "s_Graphics.h"
#include "s_UIGraphics.h"
#include "s_Portal.h"
#include "s_Map.h"
#include "s_Sounds.h"
#include "s_DroppedItems.h"
#include "s_Name.h"
#include "s_Inventory.h"
#include "s_LinkedPosition.h"
#include "s_TileChanger.h"
#include "s_Limb.h"

//sys will hold the references to the games systems
//it will initialize those and clean them up
class Sys
{
public:
	s_Map gameMap;
	s_AI aiManager;
	s_Limb limbManager;
	s_Name nameManager;
	s_WorldObject worldObjectManager;
	s_Health healthManager;
	s_Damager damageManager;
	s_Physics physicsManager;
	s_Input inputManager;
	s_Action actionManager;
	s_Graphics graphicsManager;
	s_UIGraphics UIGraphicsManager;
	s_DroppedItems droppedItemsManager;
	s_Inventory inventoryManager;
	s_LinkedPosition linkedPositionManager;
	s_TargetEntity targetEntityManger;
	s_TileChanger tileChangerManager;
	s_Portal portalManager;
	s_Sounds soundManager;

	Sys(const unsigned int& playerID, std::string& mapNameAndPath, std::shared_ptr<sf::Font> font, std::shared_ptr<sf::Event> evnt, 
		std::shared_ptr<sf::RenderWindow> window, sf::View& gameView, const bool& isGame, sf::Time& deltaTime, 
			const std::vector<unsigned int>& entityList, sf::View& UIView);
	~Sys();

	void init();
	void update(const sf::Time& dt);
	void draw();

private:

};
#endif