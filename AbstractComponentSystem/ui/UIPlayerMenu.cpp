//Evan Gordon

#include "UIPlayerMenu.h"

UIPlayerMenu::UIPlayerMenu(unsigned int ID, bool canToggle, sf::Texture& menuPanel, s_Map& mapManager): UI(canToggle, menuPanel),
						ID(ID), itemSize(0, 0, 32, 32), tempItemNumber(0), activeItemNumber(0), tileOffset(0), mapManager(mapManager), movementVector(0, 0)
{
	if(!prefabFile.load_file("xml/tiles.xml")){throw(42);}//if you're here... you dun fuckted up bud

	auto prefabs = prefabFile.first_child();
	for(auto curr = prefabs.first_child(); curr; curr = curr.next_sibling())//read in the tile objects
	{menuItems.push_back(std::make_shared<TileItem>(TileItem(mapManager.readTile(curr))));}

	for(unsigned int i = 0; i < menuItems.size(); i++)
	{
		if(i < 48)//only assign the first 48 tiles to this value
		{menuItems[i]->getSprite().setPosition((float)(1142.0 + ((i % 3) * 37)), (float)(20 + (i / 3) * 37));}//37 == width of a tile + 5 pixel space
	}
	//TODO link ptrs in all ui elements
	int tempCalc = menuItems.size() - 48;
	if(tempCalc < 0){tempCalc = 0;}
	int numberOfAllowedOffsets = (int)((tempCalc/3.0) + 0.5);
	if(numberOfAllowedOffsets < 0){numberOfAllowedOffsets = 0;}

	//newActiveCursor = UINewActiveItem_Cursor(menuPanel, sf::IntRect(190, 192, 42, 42), sf::Vector2i(activeItemMoveDistance, activeItemMoveDistance), 
						//sf::Vector2i(3, 16), sf::Vector2i(activeItemX, activeItemY), false, numberOfAllowedOffsets);
	//activeCursor = UIActiveItem_Cursor(menuPanel, sf::IntRect(148, 192, 42, 42), sf::Vector2i(activeItemMoveDistance, activeItemMoveDistance), 
						//sf::Vector2i(3, 16), sf::Vector2i(activeItemX, activeItemY), true);
	selectionCursor = Cursor(menuPanel, sf::IntRect(190, 192, 42, 42), false, menuItems[0].get());
	currentElement = Cursor(menuPanel, sf::IntRect(148, 192, 42, 42), true, menuItems[0].get());
}

bool UIPlayerMenu::toggle()
{
	if(tempItemNumber != activeItemNumber)
	{
		tempItemNumber = activeItemNumber;
		//newActiveCursor.setPosition(activeCursor.getLocationInPixels(), activeCursor.getLocationIndex());
		selectionCursor.setObj(currentElement.getObj());
	}
	return UI::toggle();
}

void UIPlayerMenu::moveActiveItem(sf::Vector2i direction)
{
	//newActiveCursor.setDrawCursor(true);
	//newActiveCursor.moveEvent(direction);
	selectionCursor.setDrawCursor(true);
	movementVector += direction;
}

c_TileChanger UIPlayerMenu::setActiveItem(std::string& mapNameAndPath)
{
	activeItemNumber = tempItemNumber;
	//activeCursor.setPosition(newActiveCursor.getLocationInPixels(), newActiveCursor.getLocationIndex());
	currentElement.setObj(selectionCursor.getObj());
	//activeCursor.checkIfMovedInBounds();
	//newActiveCursor.setDrawCursor(false);// currently need to store page information in this object, and send the bounds to new active item when it moves
	selectionCursor.setDrawCursor(false);
	return c_TileChanger(mapNameAndPath, dynamic_cast<TileItem*>(currentElement.getObj())->getTile());
}

//todo fix page changing
void UIPlayerMenu::update()
{
	//move active item
	currentElement.update();
	selectionCursor.update();
	//set  temp item number

	//newActiveCursor.update();
	//tempItemNumber = ((newActiveCursor.getLocationIndex().y - 1) * 3) + newActiveCursor.getLocationIndex().x - 1;
	//activeCursor.update();
	short int changePg = 0;//newActiveCursor.getChangePage();
	if(changePg == 1)
	{
		changePage(true);
	}
	else if(changePg == -1)
	{
		changePage(false);
	}
}

void UIPlayerMenu::draw(sf::RenderWindow& window)
{
	window.draw(image);
	//activeCursor.draw(window);
	//newActiveCursor.draw(window);
	currentElement.draw(window);
	selectionCursor.draw(window);
	
	for(int i = (int)tileOffset; i < (int)tileOffset + 48; i++)
	{
		if(i >= (int)menuItems.size()){break;}
		//window.draw(menuItems[i].draw.graphics.sprite);
		menuItems[i]->draw(window);
	}
}

void UIPlayerMenu::changePage(bool increasePage)
{
	if(checkValidPageMovement(increasePage))
	{
		if(increasePage)
		{tileOffset = tileOffset + 3;}
		else
		{tileOffset = tileOffset - 3;}

		for(size_t i = 0; i < menuItems.size(); i++)
		{
			if((short)i >= tileOffset && (short)i < (tileOffset + 48))//move tiles that will be drawn into position
			{menuItems[i]->getSprite().setPosition(1142.0f + (((i- tileOffset) % 3) * activeItemMoveDistance), 20.0f + (((i - tileOffset) / 3.0f) * activeItemMoveDistance));}
		}
	}
}

bool UIPlayerMenu::checkValidPageMovement(bool increasePage)//edit
{
	if(increasePage && (int)(menuItems.size() - 1) >= (tileOffset + 3))
	{return true;}
	else if(!increasePage && tileOffset > 0)
	{return true;}
	return false;
}

//get active tile
Tile UIPlayerMenu::getTile()
{return menuItems[activeItemNumber]->getTile();}

const int UIPlayerMenu::activeItemX = 1137;
const int UIPlayerMenu::activeItemY = 15;
const int UIPlayerMenu::activeItemMoveDistance = 37;