//Evan Gordon

#include "MapSelectState.h"

MapSelectState::MapSelectState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, bool loadMap) :IsState(window, gameEvent, gameFont),
currentMap(0), changeMap(false), loadMap(loadMap), pressN("To create new map press N", *gameFont, 26), selectedMapName(""), exit(false)
{
	//make and add background image
	///mapselector.png half way down the screen on the left side
	//split selector into two parts so it shrinks with shorter map titles
	if (!loadMap)
	{
		pressN.setString("To create new save press N");
	}

	if (!listSelectTexture.loadFromFile("images/mapSelector.png")){ throw(42); }

	selector = sf::Sprite(listSelectTexture);
	selector.setOrigin(0, selector.getTextureRect().height / 2.0f);
	selector.setPosition(0, window->getSize().y / 2.0f);
}

void MapSelectState::initialize()
{
	window->setMouseCursorVisible(false);
	newMap = false; changeMap = false; exit = false;
	mapList.clear();
	if (loadMap)
	{
		if (!listFile.load_file("xml/maps.xml"))//conditional statement that allows this to change between map selector and save file
		{
			try
			{
				throw;
			}
			catch (std::exception)
			{
				Locator::getConsole().log("serialize failed to read in .xml mapList file.");
			}
		}
		listNode = listFile.child("maps");
	}
	else
	{
		if (!listFile.load_file("xml/saves.xml"))//conditional statement that allows this to change between map selector and save file
		{
			try
			{
				throw;
			}
			catch (std::exception)
			{
				Locator::getConsole().log("serialize failed to read in .xml mapList file.");
			}
		}
		listNode = listFile.child("saves");
	}

	readList();

	if (!inputFile.load_file("xml/input.xml"))
	{
		try
		{
			throw;
		}
		catch (std::exception)
		{
			Locator::getConsole().log("serialize failed to read in .xml input prefab file.");
		}
	}
	currentMap = 0;

	inputNode = inputFile.child("input");
	up = stringToKeyboardKey(inputNode.child("playerup").child("key").text().as_string());
	down = stringToKeyboardKey(inputNode.child("playerdown").child("key").text().as_string());
	select = stringToKeyboardKey(inputNode.child("attack1").child("key").text().as_string());
}

StateType MapSelectState::update()
{
	if (Locator::getConsoleUI().getCanDraw())
	{
		Locator::getConsoleUI().readEventLog();
	}
	if (exit)
	{
		return Pop;
	}
	if (newMap && loadMap)//create new map file
	{
		return CreateMap;
	}
	if (newMap && !loadMap)//create new game file
	{
		return CreateSave;
	}
	if (changeMap && loadMap)//start editor
	{
		selectedMapName = mapList[currentMap].getString();
		return Edit;
	}
	if (changeMap && !loadMap)//play campaign
	{
		//set selectedmapname to name in save file
		selectedMapName = "xml/saves/" + mapList[currentMap].getString() + ".xml";
		pugi::xml_document selectedSaveFile;
		if (!selectedSaveFile.load_file(selectedMapName.c_str()))//load file
		{
			try
			{
				throw;
			}
			catch (std::exception)
			{
				Locator::getConsole().log("serialize failed to read in .xml mapList file.");
			}
		}
		pugi::xml_node mapNameNode = selectedSaveFile.child("currentmap");//check current
		if (mapNameNode.begin() != mapNameNode.end())
		{
			selectedMapName = mapNameNode.first_child().name();
		}
		else
		{
			try
			{
				throw;
			}
			catch (std::exception)
			{
				Locator::getConsole().log("Invalid Save File.");
			}
		}
		return Play;
	}
	else
	{
		return None;
	}
}

void MapSelectState::draw()
{
	window->draw(selector);
	window->draw(pressN);
	if (currentMap - 1 >= 0)
	{window->draw(mapList[currentMap - 1]);}
	window->draw(mapList[currentMap]);

	if (currentMap + 1 < (int)mapList.size())
	{window->draw(mapList[currentMap + 1]);}

	if (Locator::getConsoleUI().getCanDraw())
	{
		Locator::getConsoleUI().draw(*window.get());
	}
}

bool MapSelectState::handleEvents()
{
	while (window->pollEvent(*gameEvent))
	{
		switch (gameEvent->type)
		{
		case sf::Event::Closed:
			window->close();
			return true;
		case sf::Event::KeyReleased:
			if (gameEvent->key.code == sf::Keyboard::Tilde)
			{Locator::getConsoleUI().toggle();}
			break;
		case sf::Event::KeyPressed:
			if (Locator::getConsoleUI().getState() != CONSOLE)
			{
				if (gameEvent->key.code == sf::Keyboard::Escape)//stop editing current settings
				{
					exit = true;
				}
				else if (gameEvent->key.code == select)
				{
					if (mapList[0].getString() != "[None]")
					{
						changeMap = true;
					}
				}
				else if (gameEvent->key.code == up)
				{
					if (currentMap - 1 >= 0)
					{
						moveList(false);
						currentMap--;
					}
				}
				else if (gameEvent->key.code == down)
				{
					if (currentMap + 1 < (int)mapList.size())
					{
						moveList(true);
						currentMap++;
					}
				}
				else if (gameEvent->key.code == sf::Keyboard::N)
				{
					newMap = true;
				}
			}
			else
			{Locator::getConsoleUI().handleEvents(gameEvent);}
			break;
		}
	}
	return false;
}

void MapSelectState::moveList(bool down)
{
	if (down)
	{
		for (int i = 0; i < (int)mapList.size(); i++)
		{
			auto temp = mapList[i].getPosition();
			mapList[i].setPosition(temp.x, temp.y - 50);
		}
	}
	else
	{
		for (size_t i = 0; i < mapList.size(); i++)
		{
			sf::Vector2f temp = mapList[i].getPosition();
			mapList[i].setPosition(temp.x, temp.y + 50);
		}
	}
}

void MapSelectState::readList()
{
	int mapNumber = 0;
	if (listNode.first_child().name() != "")
	{
		for (pugi::xml_node curr = listNode.first_child(); curr; curr = curr.next_sibling())
		{
			sf::Text temp(curr.name(), *gameFont, 14);
			sf::FloatRect textRect = temp.getLocalBounds();
			temp.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			temp.setPosition(100, (window->getSize().y / 2.0f) + (50.0f * mapNumber));
			mapList.push_back(temp);
			mapNumber++;
		}
	}
	else//add temp blank placeholder
	{
		sf::Text temp("[None]", *gameFont, 14);
		sf::FloatRect textRect = temp.getLocalBounds();
		temp.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		temp.setPosition(100, (window->getSize().y / 2.0f) + (50.0f * mapNumber));
		mapList.push_back(temp);
	}
}

void MapSelectState::setLoadCondition(bool loadMap)
{
	this->loadMap = loadMap;
}

bool MapSelectState::getLoadCondition()
{
	return loadMap;
}

std::string MapSelectState::getSelectedMapName()
{
	if (!loadMap)
	{
		pugi::xml_document temp;
		std::string saveDataPath = "xml/saves/" + selectedMapName + ".xml";
		if (!temp.load_file(saveDataPath.c_str()))//open selected save file's xml
		{
			throw(42);
		}
		selectedMapName += "/" + std::string(temp.first_child().first_child().name());//get map name - savegame folder included, so gamestate doesnt need to search for it
		//set selectedmapname
		return selectedMapName;//return value
	}
	else
	{return selectedMapName;}
}

MapSelectState::~MapSelectState(){}