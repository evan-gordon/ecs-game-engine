//Evan Gordon

#ifndef C_GRAPHICS_H
#define C_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Component.h"

#include <string>

class c_Graphics:public Component
{
public:
	std::string textName;
	sf::Sprite sprite;
	c_Graphics();
	c_Graphics(sf::Texture& text, std::string textName, sf::Rect<int>& rect, sf::Vector2f origin);
	~c_Graphics();
};

#endif