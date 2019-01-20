//Evan Gordon

#ifndef S_MAP_H
#define S_MAP_H

#include <SFML/Graphics.hpp>
#include "../pugixml.hpp"

#include <vector>
#include <map>
#include <string>
#include <limits.h>
#include <stdint.h>

#include "components/Tile.h"
#include "components/Component.h"
#include "components/c_Graphics.h"
#include "components/c_Colidable.h"
#include "components/c_PresetName.h"
#include "../g_Functions.h"
#include "../console/Arguments.h"
#include "../services/Locator.h"

class s_Map
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::View& gameView;

	bool collisionON;
	const bool& isGame;
	std::map <std::string, sf::Texture> textures;
	typedef std::vector<std::vector<Tile>> matrix;
	matrix map;
	int mapLength, mapHeight;

public:
	s_Map(std::shared_ptr<sf::RenderWindow> window, sf::View& gameView, const bool& isGame);
	~s_Map();

	void update();
	void readMap(pugi::xml_node& mapNode, std::string& name);
	Tile readTile(pugi::xml_node node);
	void changeTile(Tile tile, sf::Vector2i position);
	sf::Vector2f checkForColision(sf::Vector2f origin, sf::Vector2f position, sf::Vector2f dimentions, sf::Vector2f &velocity);
	void noClip(const Arguments&);
	void toggleNoclip();
	void saveMap(std::string& mapName);
	void saveTile(pugi::xml_node& node, int x, int y);
	void saveTile(pugi::xml_node& node, Tile tile);
};

#endif