
#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

class UI
{
protected:
	bool canToggle, canDraw;
	sf::Sprite image;

public:

	UI();
	UI(bool canToggle, sf::Texture& image);
	virtual ~UI();

	void setPosition(float x, float y);
	//check if you can draw before drawing each time
	bool getCanDraw();

	//maybe add move location function?

	virtual bool toggle() = 0;
	virtual void update() = 0;
	void draw(sf::RenderWindow& window);
};

#endif
