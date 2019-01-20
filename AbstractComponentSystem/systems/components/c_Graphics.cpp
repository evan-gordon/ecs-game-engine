//Evan Gordon

#include "c_Graphics.h"

c_Graphics::c_Graphics() {}

c_Graphics::c_Graphics(sf::Texture& text, std::string textName, sf::Rect<int>& rect, sf::Vector2f origin)
	:sprite(), textName(textName)
{
sprite.setTexture(text);
sprite.setTextureRect(rect);
sprite.setOrigin(origin.x, origin.y);
}
	
c_Graphics::~c_Graphics() {}