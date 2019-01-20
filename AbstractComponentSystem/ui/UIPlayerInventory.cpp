//Evan Gordon
//Alexander Frisk

#include "UIPlayerInventory.h"

UIPlayerInventory::UIPlayerInventory(bool canToggle, sf::Texture& menuPanel, s_Inventory& inventoryManager, 
	s_Graphics& graphicsManager, s_Limb& limbManager) : UI(canToggle, menuPanel),
img(menuPanel), inventoryManager(inventoryManager), graphicsManager(graphicsManager), menuPosition(0), tileOffset(0), 
	state(MOVING), limbManager(limbManager), body(std::unique_ptr<BagItem>(new BagItemNormal(50, img))), movementVector(0, 0)
{
	if (!font.loadFromFile("kongtext.ttf")){throw(42);}

	for (int i = 0; i < inventorySize; i++)
	{
		bagItems.push_back(std::unique_ptr<BagItem>(new BagItemNormal(i, menuPanel)));
		auto tempPos = calcPos(i);
		
		bagItems[i].get()->setSpritePosition(tempPos.x, tempPos.y);
		auto tmp = bagItems[i].get()->getSprite();
		tmp.setOrigin(tmp.getTextureRect().width / 2.f, tmp.getTextureRect().height / 2.f);
	}
	
	//add diagonal links
	for (int i = 0; i < inventorySize; i++) {setInventoryLinkAt(i);}

	body->setSpritePosition(925, 200);

	selectionCursor = Cursor(menuPanel, sf::IntRect(190, 192, 42, 42), true, bagItems[0].get());
	currentElement = Cursor(menuPanel, sf::IntRect(148, 192, 42, 42), false, bagItems[0].get());
	selectionCursor.setPosition(dynamic_cast<BagItem*>(selectionCursor.getObj())->getSprite().getPosition());
	currentElement.setPosition(dynamic_cast<BagItem*>(currentElement.getObj())->getSprite().getPosition());
}

bool UIPlayerInventory::toggle()
{
	//activeItemNumber = 0;
	//newActiveCursor.setPosition(initialCursorPosPixels, sf::Vector2i(1, 1));
	selectionCursor.setPosition(dynamic_cast<BagItem*>(selectionCursor.getObj())->getSprite().getPosition());
	bool visible = UI::toggle();
	selectionCursor.setDrawCursor(visible);
	currentElement.setDrawCursor(false);
	//newActiveCursor.setDrawCursor(visible);
	//activeCursor.setDrawCursor(false);
	state = MOVING;
	if (visible)
	{
		for (int i = 0; i < inventorySize; i++) { updateInventorySlot(i); }
		for (int i = 0; i < inventorySize; i++) { setInventoryLinkAt(i); }
		currentElement.setObj(bagItems[0].get());
		selectionCursor.setObj(bagItems[0].get());
	}
	return visible;
}

void UIPlayerInventory::moveActiveItem(sf::Vector2i direction)
{
	switch (state)
	{
	case MOVING:
		movementVector += direction;
		break;
	case ITEMSELECTED:
		if (direction.y != 0){
			menuPosition += direction.y;
			if (menuPosition < 0)
			{menuPosition = 4;}
			else if (menuPosition > 4)
			{menuPosition = 0;}
		}
		break;
	case SWAPPING:
		movementVector += direction;
		break;
	default:
		break;
	}
}

void UIPlayerInventory::setActiveItem()
{
	currentElement.setObj(selectionCursor.getObj());
	currentElement.setPosition(dynamic_cast<BagItem*>(currentElement.getObj())->getSprite().getPosition());
	selectionCursor.setDrawCursor(false);
	currentElement.setDrawCursor(true);
}

sf::Vector2f UIPlayerInventory::calcPos(const int& position)
{
	if (position >= 0 && position < inventorySize)
	{
		return sf::Vector2f((float)(1142.0f + ((position % 3) * 37)) + 16, (float)(20.0f + (position / 3) * 37.0f) + 16) ;
	}
	return sf::Vector2f(0.f, 0.f);//invalid case
}

void UIPlayerInventory::update()
{
	auto temp = vectorToDirection(movementVector);
	if (temp != NONE)
	{
		selectionCursor.move(temp);
		selectionCursor.setPosition(dynamic_cast<BagItem*>(selectionCursor.getObj())->getSprite().getPosition());
		movementVector.x = 0;
		movementVector.y = 0;
	}
	selectionCursor.update();
	currentElement.update();

	for (int i = 0; i < inventorySize; i++){updateInventorySlot(i);}
	for (int i = 0; i < inventorySize; i++){setInventoryLinkAt(i);}
}

//update positional links for item
void UIPlayerInventory::setInventoryLinkAt(int i)
{
	if (i < 0 ||  inventorySize <= i) { return; }
	bagItems[i]->clearDirection();//reset connections
	if ((i % 3) == 0)
	{
		bagItems[i]->setDirection(RIGHT, bagItems[i + 1].get());
		bagItems[i]->setDirection(LEFT, body.get());//set left to body base
	}
	else if ((i % 3) == 2)
	{
		bagItems[i]->setDirection(LEFT, bagItems[i - 1].get());
	}
	else
	{
		bagItems[i]->setDirection(RIGHT, bagItems[i + 1].get());
		bagItems[i]->setDirection(LEFT, bagItems[i - 1].get());
	}

	if (i < 3)
	{
		bagItems[i]->setDirection(UP, bagItems[inventorySize - 3 + i].get());
		bagItems[i]->setDirection(DOWN, bagItems[i + 3].get());
	}
	else if (i >= inventorySize - 3)
	{
		bagItems[i]->setDirection(DOWN, bagItems[i - inventorySize + 3].get());
		bagItems[i]->setDirection(UP, bagItems[i - 3].get());
	}
	else
	{
		bagItems[i]->setDirection(DOWN, bagItems[i + 3].get());
		bagItems[i]->setDirection(UP, bagItems[i - 3].get());
	}
}

//get what is the active tile
sf::Sprite UIPlayerInventory::getCurrentSprite()
{
	auto temp = dynamic_cast<BagItem*>(currentElement.getObj());
	if (temp->getType() == NORMAL)
	{
		return dynamic_cast<BagItemNormal*>(currentElement.getObj())->getSprite();
	}
	return dynamic_cast<BagItemLimb*>(currentElement.getObj())->getSprite();
}

//bug is somehow in here
void UIPlayerInventory::updateInventorySlot(int position)//sync inv w invManager data
{
	if (position < 0 || position >= inventorySize){Locator::getConsole().log("Invalid inventory UI position requested: " + std::to_string(position)); return;}//bad input
	
	auto temp = inventoryManager.getItem(1, position);
	if (temp.ID == bagItems.at(position)->getID()){return;}//no change to be made
	bool updateSel = (dynamic_cast<BagItem*>(selectionCursor.getObj())->getIndex() == position);
	bool updateCurr = (dynamic_cast<BagItem*>(currentElement.getObj())->getIndex() == position);

	if (temp.isEmpty)
	{bagItems.at(position) = std::unique_ptr<BagItem>(new BagItemNormal(position, img));}
	else
	{
		if (limbManager.exists(temp.ID)){setLimbAtPosition(position, temp, *limbManager.find(temp.ID));}
		else {setItemAtPosition(position, temp);}

		bagItems.at(position)->getSprite().setRotation(0);
	}

	if (updateCurr) { currentElement.setObj(bagItems[position].get()); }
	if (updateSel) { selectionCursor.setObj(bagItems[position].get()); }
}

void UIPlayerInventory::setItemAtPosition(int position, const c_InventoryItem& invItem)
{
	sf::Sprite tempSprite = graphicsManager.components.at(invItem.ID).sprite;
	scaleSprite(tempSprite);

	bagItems.at(position) = std::unique_ptr<BagItem>(new BagItemNormal(invItem.ID, calcPos(position), 
											graphicsManager.components.at(invItem.ID).sprite, position, img));
}

void UIPlayerInventory::setLimbAtPosition(int position, const c_InventoryItem& invItem, const c_Limb& limb)
{
	//construct and insert the limb images
	auto tempLimb = limbManager.find(invItem.ID);
	LimbSect newSect;
	creatLimbSects(newSect, *tempLimb);
	bagItems.at(position) = std::unique_ptr<BagItem>(new BagItemLimb(invItem.ID, calcPos(position), 
											graphicsManager.components.at(invItem.ID).sprite, newSect, position, img));
}

void UIPlayerInventory::creatLimbSects(LimbSect& sect, const c_Limb& parent)//recursive func for building limb image
{
	for (auto it = parent.children.begin(); it != parent.children.end(); it++)
	{
		if (std::get<2>(*it) != NULL)
		{
			auto tmp = sect.children.insert(sect.children.begin(), std::make_shared<LimbSect>(LimbSect()));
			(*tmp)->sprite = graphicsManager.components.at(std::get<2>(*it)->id).sprite;
			(*tmp)->offset.x = std::get<1>(*it).x / 4.f;//4 is arbitrary, will need a more robust system for
			(*tmp)->offset.y = std::get<1>(*it).y / 4.f;//scaling the offset and images later
			creatLimbSects((**tmp), *std::get<2>(*it));
		}
	}
}

//this will need to be refined later, but for now just makes sure the individual sprite itself fits within the frame
sf::Sprite& UIPlayerInventory::scaleSprite(sf::Sprite& spr)
{
	if (spr.getTextureRect().width > 32)
	{
		float newScale = 32.f / (float)spr.getTextureRect().width;
		spr.setScale(sf::Vector2f(newScale, newScale));
	}
	if (spr.getTextureRect().height > 32)
	{
		float newScale = 32.f / (float)spr.getTextureRect().height;
		spr.setScale(sf::Vector2f(newScale, newScale));
	}
	return spr;
}

void UIPlayerInventory::select() {

	if (state == ITEMSELECTED)
	{
		state = MOVING;
		currentElement.setDrawCursor(false);
		selectionCursor.setDrawCursor(true);
		switch (menuPosition)
		{
		case 0://EQUIP
			setActiveItem();//move cursor to body and begin swapping
			selectionCursor.setDrawCursor(true);
			state = SWAPPING;
			selectionCursor.setObj(body.get());
			break;
		case 1://USE
			inventoryManager.use(1, dynamic_cast<BagItem*>(selectionCursor.getObj())->getIndex());
			break;
		case 2://MOVE
			state = SWAPPING;
			setActiveItem();
			selectionCursor.setDrawCursor(true);
			break;
		case 3://DROP
			inventoryManager.drop(1, dynamic_cast<BagItem*>(selectionCursor.getObj())->getIndex());
			break;
		default://BACK
			break;
		}
		menuPosition = 0;
	}
	else if (state == MOVING)
	{
		if (dynamic_cast<BagItem*>(selectionCursor.getObj())->isActive())
		{
			setActiveItem();
			state = ITEMSELECTED;
		}
	}
	else
	{
		state = MOVING;
		currentElement.setDrawCursor(false);
		inventoryManager.swapItemsById(1, dynamic_cast<BagItem*>(currentElement.getObj())->getID(),
			dynamic_cast<BagItem*>(selectionCursor.getObj())->getID());
		for (int i = 0; i < inventorySize; i++) { setInventoryLinkAt(i); }
	}
}

void UIPlayerInventory::draw(sf::RenderWindow& window)
{
	window.draw(image);
	drawLimbMenu(window);
	drawStatus(window);
	currentElement.draw(window);
	selectionCursor.draw(window);

	sf::Text amount;
	amount.setFont(font);
	amount.setCharacterSize(8);
	amount.setFillColor(sf::Color::White);

	drawItemMenu(window);

	for (short i = tileOffset; i < tileOffset + inventorySize; i++)
	{
		if ((size_t)i >= bagItems.size()) { break; }

		if (bagItems[i]->isActive()) {
			bagItems[i]->draw(window);
			amount.setString("item#");
			auto pos = bagItems[i]->getSprite().getPosition();
			amount.setPosition(sf::Vector2f(pos.x + 16, pos.y - 16));
			window.draw(amount);
		}
	}
}

void UIPlayerInventory::drawLimbMenu(sf::RenderWindow& window)
{
	body->draw(window);
}

void UIPlayerInventory::drawItemMenu(sf::RenderWindow& window) {
	if (state == ITEMSELECTED)
	{
		sf::RectangleShape menuBack(sf::Vector2f(150, 150));
		menuBack.setFillColor(sf::Color(100, 0, 150));
		menuBack.setPosition(sf::Vector2f(980, 200));
		window.draw(menuBack);

		menuBack.setSize(sf::Vector2f(130, 20));
		menuBack.setFillColor(sf::Color(200, 200, 0));
		menuBack.setPosition(sf::Vector2f(990.0f, 220.0f + (float)(24.0f*menuPosition)));
		window.draw(menuBack);

		std::vector<std::string> strings;
		strings.push_back("EQUIP");
		strings.push_back("USE");
		strings.push_back("MOVE");
		strings.push_back("DROP");
		strings.push_back("BACK");
		sf::Text options;
		options.setFont(font);
		options.setCharacterSize(16);
		auto color = generateOptionsColor();
		for (int i = 0; i < (int)strings.size(); i++) {
			options.setFillColor(color[0]);
			options.setString(strings[i]);
			options.setPosition(sf::Vector2f(1000.0f, 220.0f + i*24.0f));
			window.draw(options);
		}
	}
}

void UIPlayerInventory::drawStatus(sf::RenderWindow& window)
{
	sf::RectangleShape red(sf::Vector2f(80, 10));
	sf::RectangleShape green(sf::Vector2f(80.0f/**status.hp/status.maxHp*/, 10.0f));
	red.setPosition(sf::Vector2f(1158, 448));
	green.setPosition(sf::Vector2f(1158, 448));
	red.setFillColor(sf::Color::Red);
	green.setFillColor(sf::Color::Green);
	window.draw(red);
	window.draw(green);

	sf::Text healthText;
	healthText.setFont(font);
	healthText.setCharacterSize(12);
	healthText.setFillColor(sf::Color::White);
	healthText.setString("former health text");
	healthText.setPosition(1152, 432);
	window.draw(healthText);
}

std::vector<sf::Color> UIPlayerInventory::generateOptionsColor()
{
	std::vector<sf::Color> color;
	color.push_back(sf::Color::White);
	return color;
}

const int UIPlayerInventory::activeItemX = 1137;
const int UIPlayerInventory::activeItemY = 15;
const int UIPlayerInventory::activeItemMoveDistance = 37;
const int UIPlayerInventory::inventorySize = 30;