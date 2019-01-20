//Evan Gordon

#include "s_Map.h"

s_Map::s_Map(std::shared_ptr<sf::RenderWindow> window, sf::View& gameView, const bool& isGame) :
	isGame(isGame), mapLength(0), mapHeight(0), map(), window(window), gameView(gameView), textures(), collisionON(true)
{
	textures.insert(std::make_pair("images/overWorld.png", sf::Texture()));
	if(!textures["images/overWorld.png"].loadFromFile("images/overWorld.png"))
	{
		try
		{throw;}
		catch (std::exception e)
		{Locator::getConsole().log("images/overWorld.png could not be loaded");}
	}
}

//Nulla è reale, tutto è lecito. Requiescat en pace...
void s_Map::update()
{
	window->setView(gameView);

	for(int i = 0; i < mapLength; i++)
	{
		for(int j = 0; j < mapHeight; j++)
		{
			window->draw(map[i][j].graphics.sprite);
		}	
	}	
}

void s_Map::readMap(pugi::xml_node& mapNode, std::string& mapName)
{
	mapLength = mapNode.child("width").text().as_int();
	mapHeight = mapNode.child("height").text().as_int();
	map.resize(mapLength);
	for(int i = 0; i < mapLength; i++)
	{map[i].resize(mapHeight);}

	pugi::xml_node cursor = mapNode.child("map");
	std::string cursorName;
	for(int x = 0; x < mapLength; x++)
	{
		cursorName =  "x" + std::to_string(x);
		cursor = cursor.child(cursorName.c_str());
		for(int y = 0; y < mapHeight; y++)
		{
			cursorName =  "y" + std::to_string(y); 
			cursor = cursor.child(cursorName.c_str());
			pugi::xml_node tilePrefab = cursor.first_child();
			Tile tile;
			if(tilePrefab == NULL)
			{
				Locator::getConsole().log("Error no tile prefab with " + mapName + " found u wot m8?");
				break;
			}
			else
			{tile = readTile(tilePrefab);}
			map[x][y] = tile;
			map[x][y].graphics.sprite.setPosition(x * 32.0f, y * 32.0f);
			cursor = cursor.parent();
		}	
		cursor = cursor.parent();
	}	
}

void s_Map::saveMap(std::string& mapName)
{
	Locator::getConsole().log("Saving " + mapName);
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(mapName.c_str());
	if(!result)
	{
		Locator::getConsole().log("Load result: " + std::string(result.description()) + ", mesh name: " + document.child("mesh").attribute("name").value());
		try
		{throw;}
		catch(std::exception e)
		{Locator::getConsole().log("Error: Failed to find " + mapName + " the file was either moved or damaged.");}
	}
	auto node = document.child("node");
	node.child("width").text() = mapLength;
	node.child("height").text() = mapHeight;
	pugi::xml_node cursor = node.child("map");
	int i = 0;
	while (cursor.first_child() != NULL)//delete old contents
	{
		std::string childName = "x" + std::to_string(i);
		cursor.remove_child(childName.c_str());
		i++;
	}

	std::string cursorName;
	for(int x = 0; x < mapLength; x++)
	{
		cursorName =  "x" + std::to_string(x);
		cursor.append_child(cursorName.c_str());
		cursor = cursor.child(cursorName.c_str());
		for(int y = 0; y < mapHeight; y++)
		{
			cursorName =  "y" + std::to_string(y); 
			cursor.append_child(cursorName.c_str());
			cursor = cursor.child(cursorName.c_str());
			saveTile(cursor, x, y);
			cursor = cursor.parent();
		}	
		cursor = cursor.parent();
	}
	document.save_file(mapName.c_str());
	Locator::getConsole().log("Map saving completed.");
}

void s_Map::saveTile(pugi::xml_node& node, int x, int y)
{
	Tile temp = map[x][y];
	saveTile(node, temp);
}

void s_Map::saveTile(pugi::xml_node& node, Tile tile)
{
	//editing tile starts here- Tile's name is first made the node name
	node.append_child(tile.name.name.c_str());
	pugi::xml_node tileNode = node.child(tile.name.name.c_str());
	//adding components here
	tileNode.append_child("colidable");
	tileNode.child("colidable").append_child("iscolidable");
	tileNode.child("colidable").child("iscolidable").text() = std::to_string(tile.colidable.isColidable).c_str();
	//graphics.saveToFile();
	tileNode.append_child("graphics");
	pugi::xml_node graphics = tileNode.child("graphics");
	graphics.append_child("x");
	graphics.append_child("y");
	graphics.append_child("width");
	graphics.append_child("height");
	graphics.append_child("originx");
	graphics.append_child("originy");

	graphics.child("x").text() = std::to_string(tile.graphics.sprite.getTextureRect().left).c_str();
	graphics.child("y").text() = std::to_string(tile.graphics.sprite.getTextureRect().top).c_str();
	graphics.child("width").text() = std::to_string(tile.graphics.sprite.getTextureRect().width).c_str();
	graphics.child("height").text() = std::to_string(tile.graphics.sprite.getTextureRect().height).c_str();
	graphics.child("originx").text() = std::to_string(tile.graphics.sprite.getOrigin().x).c_str();
	graphics.child("originy").text() = std::to_string(tile.graphics.sprite.getOrigin().y).c_str();
}

Tile s_Map::readTile(pugi::xml_node node)
{
	Tile newTile;
	pugi::xml_node component = node.first_child();
	newTile.name.name = node.name();
	newTile.colidable.isColidable = component.child("iscolidable").text().as_bool();

	component = component.next_sibling();//switch to graphics component
	sf::Vector2f location, size, origin;
	location.x = (float)component.child("x").text().as_int();
	location.y = (float)component.child("y").text().as_int();
	size.x = (float)component.child("width").text().as_int();
	size.y = (float)component.child("height").text().as_int();
	origin.x = (float)component.child("originx").text().as_int();
	origin.y = (float)component.child("originy").text().as_int();
	newTile.graphics = c_Graphics(textures.at("images/overWorld.png"), "images/overWorld.png", sf::Rect<int>((int)location.x, (int)location.y, (int)size.x, (int)size.y), origin);

	return newTile;
}

void s_Map::changeTile(Tile tile, sf::Vector2i position){map[position.x][position.y] = tile;}

//Function for handling colisions with Map tiles. Returns newPosition
sf::Vector2f s_Map::checkForColision(sf::Vector2f origin, sf::Vector2f position, sf::Vector2f dimentions, sf::Vector2f &velocity)//pass in velocity too?
{
	if(collisionON)
	{
		sf::Vector2f halfWidth(dimentions.x/2.0f, dimentions.y/2.0f);
		sf::Vector2f center(position.x - origin.x + halfWidth.x, position.y - origin.y + halfWidth.y);
		
		if (center.x + halfWidth.x < 0 || center.y + halfWidth.y < 0){ return sf::Vector2f(0.0f, 0.0f); }//if outside the map entirely

		//define tiles that will be searched, make sure to only search within the map
		sf::Vector2i topLeftIndex((int)((center.x - halfWidth.x - 0.5f)/32.0f), (int)((center.y - halfWidth.y - 0.5f)/32.0f));
		if(topLeftIndex.x < 0){topLeftIndex.x = 0;}
		if(topLeftIndex.y < 0){topLeftIndex.y = 0;}
		if(topLeftIndex.x >= (int)map.size() || topLeftIndex.y >= (int)map[topLeftIndex.x].size()){return sf::Vector2f(0.0f, 0.0f);}
		sf::Vector2i bottomRightIndex((int)((center.x + halfWidth.x + 0.5f)/32.0f), (int)((center.y + halfWidth.y + 0.5f)/32.0f));
		if(bottomRightIndex.x >= (int)map.size()){bottomRightIndex.x = map.size() - 1;}
		if(bottomRightIndex.y >= (int)map[bottomRightIndex.x].size()){bottomRightIndex.y = map[bottomRightIndex.x].size() - 1;}
		if(bottomRightIndex.x < 0 || bottomRightIndex.y < 0){return sf::Vector2f(0.0f, 0.0f);}

		//scan all nearby tiles
		bool collisionOccured = true;
		sf::Vector2f result(0,0);//used to store the adjusted offset that will be returned
		while(collisionOccured)
		{
			collisionOccured = false;
			std::vector<sf::Vector2f> collisionResult;
			for(int i = topLeftIndex.x; i <= bottomRightIndex.x; i++)
			{
				for(int j = topLeftIndex.y; j <= bottomRightIndex.y; j++)
				{
					if(map[i][j].colidable.isColidable)//then check for colision
					{
						sf::Vector2f temp(center.x + result.x, center.y + result.y);//temp stores the adjusted position of object
						sf::Vector2f resultVector = boxToStaticBoxCollision(temp, halfWidth, velocity,  sf::Vector2f((i * 32.0f) + 16.0f, (j * 32.0f) + 16.0f), sf::Vector2f(16, 16));
						if(resultVector.x != 0 || resultVector.y != 0)
						{
						collisionOccured = true;
						collisionResult.push_back(resultVector);
						}
					}
				}
			}			
			if(collisionOccured)//find smallest value in collisionResult and add it to result then repeat
			{
				sf::Vector2f smallest(LDBL_MAX_EXP, LDBL_MAX_EXP);//used to use UINT_MAX, but there were type conversion errors, maybe need to fix later
				for(auto it = collisionResult.begin(); it != collisionResult.end(); it++)
				{
					if(smallest.x == LDBL_MAX_EXP || smallest.y == LDBL_MAX_EXP || (it->x + it->y) > (smallest.x + smallest.y))
					{
						smallest = *it;
					}
				}
				result.x += smallest.x;
				result.y += smallest.y;
			}
		}
		return result;
	}
	return sf::Vector2f(0, 0);
}

void s_Map::noClip(const Arguments&){toggleNoclip();}

void s_Map::toggleNoclip()
{
	if(collisionON)
	{collisionON = false;}
	else
	{collisionON = true;}
}

s_Map::~s_Map() {}