//Evan Gordon
#include "UIInfo.h"

UIInfo::UIInfo(std::shared_ptr<sf::Font> font) :
	font(font), prevTime(0)
{
	displays.insert(std::make_pair<InfoType, Info>(FPS, Info("0fps", *font)));
	displays[FPS].canDraw = true;//remove later
}

void UIInfo::update()
{
	displays[FPS].setText(std::to_string((int)(1.0f / c.restart().asSeconds())));
}

bool UIInfo::toggle() { return UI::toggle(); }

void UIInfo::toggleInfo(InfoType type) { displays[type].toggle(); }

void UIInfo::draw(sf::RenderWindow& window) { displays[FPS].draw(window); }

UIInfo::~UIInfo() {}