#ifndef UIINFO_H
#define UIINFO_H

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <map>


#include "UI.h"

enum InfoType{ FPS, TIMEMILIS };

struct Info
{
	bool canDraw;
	sf::Text text;
	sf::RectangleShape background;

	Info::Info() {}
	Info::Info(sf::String t, sf::Font& f):
		text(t, f, 12)
	{
		background.setSize(sf::Vector2f(70.f, 18.f));
		background.setFillColor(sf::Color(0, 0, 0, 125));
		text.setPosition(66, 14);
		text.setOrigin(text.getLocalBounds().width, 0);
	}

	void Info::toggle()
	{
		if(canDraw)
		{
			canDraw = false;
			return;
		}
		canDraw = true;
	}

	void Info::setText(std::string str)
	{
		text.setString(str + "fps");
		text.setPosition(66, 14);
		text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
	}

	void Info::draw(sf::RenderWindow& window)
	{
		if (canDraw)
		{
			window.draw(background);
			window.draw(text);
		}
	}
};

class UIInfo : public UI
{
public:
	UIInfo(std::shared_ptr<sf::Font> font);
	~UIInfo();

	void update();
	bool toggle();
	void toggleInfo(InfoType type);
	void draw(sf::RenderWindow& window);

private:
	sf::Clock c;
	sf::Time t;
	float prevTime;
	std::shared_ptr<sf::Font> font;
	std::map<InfoType, Info> displays;
};
#endif // !UIINFO_H

