
#include "UI.h"

UI::UI():
	canDraw(true), canToggle(true)
{}

UI::UI(bool canToggle, sf::Texture& image):
	canDraw(true), canToggle(canToggle), image(image)
{}

void UI::setPosition(float x, float y){image.setPosition(x, y);}

bool UI::toggle()
{
	if(canToggle)
	{
		if(canDraw)
		{
			canDraw = false;
			return canDraw;
		}
		else
		{
			canDraw = true;
			return canDraw;
		}
	}
	return false;
}

void UI::update() {}

void UI::draw(sf::RenderWindow& window){window.draw(image);}

bool UI::getCanDraw(){return canDraw;}

UI::~UI() {}