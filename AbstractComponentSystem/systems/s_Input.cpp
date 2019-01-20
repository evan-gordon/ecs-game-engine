//Evan Gordon

#include "s_Input.h"

s_Input::s_Input(std::shared_ptr<sf::Event> event, std::map<unsigned int, c_Physics>& physicsComponents, s_Action& actionsManager, s_Inventory& inventoryManager, s_UIGraphics& UIGraphicsManager, s_Sounds& soundManager) :
event(event), physicsComponents(physicsComponents), actionsManager(actionsManager), inventoryManager(inventoryManager), UIGraphicsManager(UIGraphicsManager), soundManager(soundManager)
{
	if (!input.load_file("xml/input.xml"))
	{
		try{throw;}
		catch (std::exception)
		{Locator::getConsole().log("serialize failed to read in .xml input prefab file.");}
	}
	inputReader = input.child("input");
}

std::string s_Input::update()
{
	//fix later ----- move this into loop --- if this is the right event return type name as broadcast message
	if (!UIGraphicsManager.isMenuOpen())
	{
		if (event->type == components.at("attack1").eventType &&
			((event->key.code == components.at("attack1").keyboardInput) || (event->key.code == components.at("attack1").mouseInput)))
		{
			return "attack1";
		}
		if (event->type == components.at("weaponmenu").eventType &&
			((event->key.code == components.at("weaponmenu").keyboardInput) || (event->key.code == components.at("weaponmenu").mouseInput)))
		{
			//special case for exit menu being open
			auto weaponID = inventoryManager.getWeapon(1);
			if (weaponID != 0)
			{
				UIGraphicsManager.togglePlayerMenu(weaponID);//UIGraphics handles checking if weapon has menu
			}
		}
		if (event->type == components.at("inventorymenu").eventType &&
			((event->key.code == components.at("inventorymenu").keyboardInput) || (event->key.code == components.at("inventorymenu").mouseInput)))
		{
			//special case for exit menu being open
			UIGraphicsManager.playerInventoryMenu->toggle();
		}
		if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Tilde)
		{
			Locator::getConsoleUI().toggle();
			return "";
		}
		if (event->type == sf::Event::Closed || (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape))
		{
			UIGraphicsManager.exitMenu.toggle();
		}
		//more cases later for different types of input
	}
	else//update ui
	{
		//case out different ui's
		if (/*inventoryManager.getWeapon(1) == 100 && */UIGraphicsManager.wrenchMenu->getCanDraw()) //really cheaty way to do this
		{
			if (event->type == components.at("weaponmenu").eventType &&
				((event->key.code == components.at("weaponmenu").keyboardInput) || (event->key.code == components.at("weaponmenu").mouseInput)))
			{
				UIGraphicsManager.wrenchMenu->toggle();//change this later to accomodate for different menus
			}
			if (event->type == components.at("attack1").eventType &&
				((event->key.code == components.at("attack1").keyboardInput) || (event->key.code == components.at("attack1").mouseInput)))
			{
				auto weapon = inventoryManager.getWeapon(1);
				if (weapon != 0)
				{
					UIGraphicsManager.select(weapon);
				}
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerup").keyboardInput) || (event->key.code == components.at("playerup").mouseInput)))
			{
				auto weapon = inventoryManager.getWeapon(1);
				if (weapon != 0)
				{
					UIGraphicsManager.move(weapon, sf::Vector2i(0, -1));
				}
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerdown").keyboardInput) || (event->key.code == components.at("playerdown").mouseInput)))
			{
				auto weapon = inventoryManager.getWeapon(1);
				if (weapon != 0)
				{
					UIGraphicsManager.move(weapon, sf::Vector2i(0, 1));
				}
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerleft").keyboardInput) || (event->key.code == components.at("playerleft").mouseInput)))
			{
				auto weapon = inventoryManager.getWeapon(1);
				if (weapon != 0)
				{
					UIGraphicsManager.move(weapon, sf::Vector2i(-1, 0));
				}
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerright").keyboardInput) || (event->key.code == components.at("playerright").mouseInput)))
			{
				auto weapon = inventoryManager.getWeapon(1);
				if (weapon != 0)
				{
					UIGraphicsManager.move(weapon, sf::Vector2i(1, 0));
				}
			}
			if (event->type == sf::Event::Closed)
			{
				UIGraphicsManager.exitMenu.toggle();
				UIGraphicsManager.wrenchMenu->toggle();
			}
			if (event->type == sf::Event::EventType::KeyPressed && event->key.code == sf::Keyboard::Escape)
			{
				UIGraphicsManager.wrenchMenu->toggle();
			}
		}
		else if (UIGraphicsManager.playerInventoryMenu->getCanDraw())
		{
			if (event->type == components.at("inventorymenu").eventType &&
				((event->key.code == components.at("inventorymenu").keyboardInput) || (event->key.code == components.at("inventorymenu").mouseInput)))
			{
				UIGraphicsManager.playerInventoryMenu->toggle();
			}
			if (event->type == sf::Event::Closed)
			{
				UIGraphicsManager.exitMenu.toggle();
				UIGraphicsManager.playerInventoryMenu->toggle();
			}
			if (event->type == sf::Event::EventType::KeyPressed && event->key.code == sf::Keyboard::Escape)
			{
				UIGraphicsManager.playerInventoryMenu->toggle();
			}
			if (event->type == components.at("attack1").eventType &&
				((event->key.code == components.at("attack1").keyboardInput) || (event->key.code == components.at("attack1").mouseInput)))
			{
				UIGraphicsManager.select(1);
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerup").keyboardInput) || (event->key.code == components.at("playerup").mouseInput)))
			{
				UIGraphicsManager.move(1, sf::Vector2i(0, -1));
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerdown").keyboardInput) || (event->key.code == components.at("playerdown").mouseInput)))
			{
				UIGraphicsManager.move(1, sf::Vector2i(0, 1));
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerleft").keyboardInput) || (event->key.code == components.at("playerleft").mouseInput)))
			{
				UIGraphicsManager.move(1, sf::Vector2i(-1, 0));
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerright").keyboardInput) || (event->key.code == components.at("playerright").mouseInput)))
			{
				UIGraphicsManager.move(1, sf::Vector2i(1, 0));
			}
		}
		else if (UIGraphicsManager.exitMenu.getCanDraw())
		{
			if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape)
			{
				UIGraphicsManager.exitMenu.toggle();
			}
			if ((event->type == components.at("attack1").eventType &&
				((event->key.code == components.at("attack1").keyboardInput) || (event->key.code == components.at("attack1").mouseInput)))
				|| event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Return)
			{
				UIGraphicsManager.exitMenu.update();
			}
			//if ((event->key.code == components.at("drop").keyboardInput) || (event->key.code == components.at("drop").mouseInput))
			//{
			//	inventoryManager.drop(1);
			//}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerup").keyboardInput) || (event->key.code == components.at("playerup").mouseInput)))
			{
				UIGraphicsManager.exitMenu.cancelSelected = false;
				UIGraphicsManager.exitMenu.moveSelector();
			}
			if (event->type == sf::Event::KeyPressed &&
				((event->key.code == components.at("playerdown").keyboardInput) || (event->key.code == components.at("playerdown").mouseInput)))
			{
				UIGraphicsManager.exitMenu.cancelSelected = true;
				UIGraphicsManager.exitMenu.moveSelector();
			}
		}
		else if (Locator::getConsoleUI().getState() == CONSOLE)
		{
			Locator::getConsoleUI().handleEvents(event);
		}
	}
	return "";
}

//This function accepts the input event for the player as he's playing the game, not using a UI menu
std::string s_Input::updateIsKeyPressed()//change to update isKeyPressedEvents
{
	if (!UIGraphicsManager.isMenuOpen())//if moved update actionComponent
	{
		int lookAngle = -1;
		if (sf::Keyboard::isKeyPressed(components.at("playerup").keyboardInput))//move up
		{
			if (components.at("playerdown").eventType == sf::Event::KeyReleased && sf::Keyboard::isKeyPressed(components.at("playerdown").keyboardInput))
			{}
			else
			{
				lookAngle = 270;//up
			}
		}
		else if (sf::Keyboard::isKeyPressed(components.at("playerdown").keyboardInput))//move down
		{
			lookAngle = 90;//down
		}

		if (sf::Keyboard::isKeyPressed(components.at("playerleft").keyboardInput))//move left
		{
			if (sf::Keyboard::isKeyPressed(components.at("playerright").keyboardInput))
			{}
			else
			{
				if (lookAngle == -1)//left
				{
					lookAngle = 180;
				}
				else if (lookAngle == 90)
				{
					lookAngle = 135;
				}
				else
				{
					lookAngle = 225;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(components.at("playerright").keyboardInput))//move right
		{
			if (lookAngle == -1)//right
			{
				lookAngle = 0;
			}
			else if (lookAngle == 90)
			{
				lookAngle = 45;
			}
			else
			{
				lookAngle = 315;
			}
			
		}
		actionsManager.setAction(1, lookAngle/*up, down, left, right*/);//update movement for player
		if (lookAngle >= 0/*(up || down || left || right) == true*/)
		{
			soundManager.playSound(1, STONESTEP);
		}
	}
	return "";
}

void s_Input::readFromFile()
{
	for (pugi::xml_node inputs = inputReader.first_child(); inputs; inputs = inputs.next_sibling())
	{
		std::string inputName = inputs.name();
		std::string key = inputs.child("key").text().as_string();

		//0 for keyPressed, and 1 for mouse input, and 2 for isKeyPressed when read in from file iskeypressed needs its own update function
		int inputType = inputs.child("type").text().as_int();
		if (inputType == 0)
		{
			c_Input newInput(sf::Event::KeyPressed, stringToKeyboardKey(key));
			addComponent(inputName, newInput);
		}
		else if (inputType == 1)
		{
			c_Input newInput(sf::Event::MouseButtonPressed, stringToMouseButton(key));
			addComponent(inputName, newInput);
		}
		else
		{
			c_Input newInput(sf::Event::KeyReleased, stringToKeyboardKey(key));//currently only keyboard input is allowed for player movement
			addComponent(inputName, newInput);
		}
	}
}

void s_Input::addComponent(std::string name, c_Input& newComponent)
{
	components.insert(std::pair<std::string, c_Input>(name, newComponent));
}

const std::map<std::string, c_Input>& s_Input::getComponentsMap()
{
	return components;
}

s_Input::~s_Input() {}