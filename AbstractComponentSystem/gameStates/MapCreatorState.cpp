//Evan Gordon

#include "MapCreatorState.h"

MapCreatorState::MapCreatorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont, const bool& createMap) :IsState(window, gameEvent, gameFont),
createMap(createMap), newFile("Map Name:", *gameFont, 14), width("Width", *gameFont, 14), height("Height", *gameFont, 14),
nameInput("", *gameFont, 14), wInput("", *gameFont, 14), hInput("", *gameFont, 14),
nameEntered(false), widthEntered(false), heightEntered(false)
{
	newFile.setPosition(window->getSize().x / 2.0f - newFile.getLocalBounds().width, window->getSize().y / 2.0f - 25.0f);
	nameInput.setPosition(window->getSize().x / 2.0f + 5.0f, window->getSize().y / 2.0f - 25.0f);
	width.setPosition(window->getSize().x / 2.0f - width.getLocalBounds().width, window->getSize().y / 2.0f);
	wInput.setPosition(window->getSize().x / 2.0f + 5.0f, window->getSize().y / 2.0f);
	height.setPosition(window->getSize().x / 2.0f - height.getLocalBounds().width, window->getSize().y / 2.0f + 25.0f);
	hInput.setPosition(window->getSize().x / 2.0f + 5.0f, window->getSize().y / 2.0f + 25.0f);

	if (createMap)
	{
		if (!mapList.load_file("xml/maps.xml")){ throw(42); }

		if (!tilePrefab.load_file("xml/tiles.xml")){ throw(42); }
	}
	else
	{
		newFile.setString("Name:");
		if (!savesList.load_file("xml/saves.xml")){ throw(42); }

		if (!campaignMaps.load_file("xml/campaignmaps.xml")){ throw(42); }
	}
	if (!backText.loadFromFile("images/mapCreator.png")){ throw(42); }
	background.setTexture(backText);
}

void MapCreatorState::initialize()
{
	nameEntered = false;
	nameInput.setString("");
	widthEntered = false;
	wInput.setString("");
	heightEntered = false;
	hInput.setString("");
	newXMLFile(NULL);
}

StateType MapCreatorState::update()//FOR GONDOR!
{
	if (Locator::getConsoleUI().getCanDraw())
	{
		Locator::getConsoleUI().readEventLog();
	}

	if (createMap && nameEntered && widthEntered && heightEntered)
	{
		generateMap();
		return Pop;
	}
	else if (!createMap && nameEntered)
	{
		generateSave();
		return Pop;
	}
	else
	{
		return None;
	}
}

void MapCreatorState::draw()
{
	window->draw(background);
	window->draw(newFile);
	window->draw(nameInput);
	if (createMap)
	{
		window->draw(width);
		window->draw(wInput);
		window->draw(height);
		window->draw(hInput);
	}

	if (Locator::getConsoleUI().getCanDraw())
	{
		Locator::getConsoleUI().draw(*window.get());
	}
}

//add a check for duplicate maps, check to see if info is correct later, and add sounds
bool MapCreatorState::handleEvents()
{
	while (window->pollEvent(*gameEvent))
	{
		switch (gameEvent->type)
		{
		case sf::Event::Closed:
			window->close();
			return true;
		default:
			break;
		}
		if (Locator::getConsoleUI().getState() != CONSOLE)
		{
			if (gameEvent->type == sf::Event::KeyReleased && gameEvent->key.code == sf::Keyboard::Tilde)
			{
				Locator::getConsoleUI().toggle();
			}
			if ((createMap && !nameEntered || !widthEntered || !heightEntered) || (!createMap && !nameEntered))
			{
				if (gameEvent->type == sf::Event::KeyReleased)
				{
					if (gameEvent->key.code == sf::Keyboard::Return)//change to next input
					{
						if (!nameEntered && nameInput.getString().getSize() > 0)
						{
							nameEntered = true;
						}
						else if (!widthEntered && wInput.getString().getSize() > 0)
						{
							widthEntered = true;
						}
						else if (hInput.getString().getSize() > 0)
						{
							heightEntered = true;
						}
					}
					else if (gameEvent->key.code == sf::Keyboard::BackSpace)
					{
						if (!nameEntered && nameInput.getString().getSize() > 0)
						{
							std::string temp = nameInput.getString();
							temp.resize(temp.size() - 1);
							nameInput.setString(temp);
						}
						else if (!widthEntered && wInput.getString().getSize() > 0)
						{
							std::string temp = wInput.getString();
							temp.resize(temp.size() - 1);
							wInput.setString(temp);
						}
						else if (!heightEntered && hInput.getString().getSize() > 0)
						{
							std::string temp = hInput.getString();
							temp.resize(temp.size() - 1);
							hInput.setString(temp);
						}
					}
				}
				else if (gameEvent->type == sf::Event::TextEntered && (gameEvent->text.unicode > 0x02F && gameEvent->text.unicode < 0x03A) ||
					(gameEvent->text.unicode > 0x040 && gameEvent->text.unicode < 0x05B) ||
					(gameEvent->text.unicode > 0x060 && gameEvent->text.unicode < 0x07B))//take raw text and turn it into the input
				{
					if (!nameEntered)
					{
						if (nameInput.getString().getSize() < 15)//take raw input
						{
							sf::String currentText = nameInput.getString();
							currentText = currentText + static_cast<char>(gameEvent->text.unicode);
							nameInput.setString(currentText);
						}
					}
					else
					{
						if (gameEvent->text.unicode > 0x02F && gameEvent->text.unicode < 0x03A)//4 digit #
						{
							if (!widthEntered)
							{
								if (wInput.getString().getSize() < 4)
								{
									wInput.setString(wInput.getString() + static_cast<char>(gameEvent->text.unicode));
								}
								else if (wInput.getString().getSize() >= 4)
								{
									//play a sound
								}
							}
							else if (!heightEntered)
							{
								if (hInput.getString().getSize() < 4)
								{
									hInput.setString(hInput.getString() + static_cast<char>(gameEvent->text.unicode));
								}
								else if (hInput.getString().getSize() >= 4)
								{
									//play a sound
								}
							}
						}
					}
				}
			}
		}
		else
		{
			Locator::getConsoleUI().handleEvents(gameEvent);
		}
	}
	return false;
}

void MapCreatorState::generateMap()
{
	newXMLFile(NULL);

	pugi::xml_node node = newXMLFile.append_child("node");
	pugi::xml_node width = node.append_child("width");
	std::string tempWidth = wInput.getString();
	width.append_child(pugi::node_pcdata).set_value(tempWidth.c_str());
	pugi::xml_node height = node.append_child("height");
	std::string tempHeight = hInput.getString();
	height.append_child(pugi::node_pcdata).set_value(tempHeight.c_str());
	pugi::xml_node map = node.append_child("map");
	node.append_child("items");

	//fill with tiles
	pugi::xml_node temp = tilePrefab.first_child();
	pugi::xml_node tile = temp.child("dirtmiddlemiddle");//node that contains the prefab of tile

	int intWidth = atoi(tempWidth.c_str());
	int intHeight = atoi(tempHeight.c_str());

	pugi::xml_node icursor;
	pugi::xml_node jcursor;
	for (int i = 0; i < intWidth; i++)
	{
		std::string itempStr = "x" + std::to_string(i);
		icursor = map.append_child(itempStr.c_str());
		itempStr = "";
		for (int j = 0; j < intHeight; j++)
		{
			std::string jtempStr = "y" + std::to_string(j);
			jcursor = icursor.append_child(jtempStr.c_str());
			jcursor.append_copy(tile);
			jtempStr = "";
		}
	}//Save file
	std::string tempMapName = "xml/maps/" + nameInput.getString() + ".xml";
	newXMLFile.save_file(tempMapName.c_str());

	pugi::xml_node mapListNode = mapList.child("maps");//add new file to maps.xml
	if (mapListNode.name() != "")
	{
		std::string temp = nameInput.getString();
		mapListNode.append_child(temp.c_str());
		mapList.save_file("xml/maps.xml");
	}
	else
	{
		throw(42);
	}
}

//make sure player is in starting map when generated
//because this will need to create a new directory, will be os specific, only doing windows for now
//also needs to check for existing save name
void MapCreatorState::generateSave()
{
	newXMLFile(NULL);

	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring tempString(buffer);
	tempString = tempString.substr(0, tempString.find_last_of(L"\\/"));// current project path is now in string
	tempString += "\\xml\\saves\\" + nameInput.getString();//edit current path to get to save location
	if (!CreateDirectory(tempString.c_str(), NULL))//create file for saves ---- how?
	{
		//file creation failed, log in console
		return;
	}
	pugi::xml_node mapsToCopy = campaignMaps.child("campaignmaplist").first_child();//add copy of all maps that need to be copied into file
	for (mapsToCopy; mapsToCopy; mapsToCopy = mapsToCopy.next_sibling())
	{
		pugi::xml_document mapCopy;
		pugi::xml_document originalMap;
		std::string docName = "xml/maps/" + nameInput.getString() + ".xml";//
		if (!originalMap.load_file(docName.c_str()))
		{
			throw(42);//doc didnt load
		}
		else
		{
			docName = "xml/saves/" + nameInput.getString() + "/" + mapsToCopy.name() + ".xml";//new file name
			mapCopy.reset(originalMap);//xml_document is non copyable
			mapCopy.save_file(docName.c_str());//save new file
		}
	}

	//Save File
	pugi::xml_node node = newXMLFile.append_child("currentmap");
	node.append_child(campaignMaps.child("campaignstartingmap").first_child().name());//set first map
	std::string tempMapName = "xml/saves/" + nameInput.getString() + ".xml";
	newXMLFile.save_file(tempMapName.c_str());//save save game file

	pugi::xml_node savesListNode = savesList.child("saves");//add new file to saves.xml
	if (savesListNode.name() != "")
	{
		std::string temp = nameInput.getString();
		savesListNode.append_child(temp.c_str());
		savesList.save_file("xml/saves.xml");
	}
	else
	{
		throw(42);
	}
}

MapCreatorState::~MapCreatorState(){}