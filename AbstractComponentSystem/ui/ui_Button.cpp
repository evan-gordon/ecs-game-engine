#include "ui_Button.h"

ui_Button::ui_Button()
{}

ui_Button::ui_Button(sf::Texture& normal, sf::Texture& clicked, sf::Vector2f location)
:normal(normal), clicked(clicked), /*currentSpr(&(this->normal)),*/ location(location),
		delay(sf::seconds(2.0f/60.0f)), delayPush(sf::seconds(2.0f/60.0f)), isPushed(false)
{
    this->normal.setPosition(location);
    this->clicked.setPosition(location);
}

ui_Button::ui_Button(sf::Texture& normal, sf::Texture& clicked, std::string text, sf::Vector2f location, sf::Font& font, sf::Time pressDelay)
:normal(normal), clicked(clicked), /*currentSpr(&(this->normal)),*/location(location),
		delay(pressDelay), delayPush(pressDelay), isPushed(false),
			text(text, font, 14)
{
	this->normal.setPosition(location);
	this->clicked.setPosition(location);
    this->text.setPosition(location.x + 12, location.y + 8);
	this->text.setFillColor(sf::Color::Blue);
	this->clicked.setPosition(location);
	/*setSprite(false);*/
}

bool ui_Button::checkIfClick (const sf::Vector2f& mousePos)
{
	if (mousePos.x > location.x && mousePos.x<(location.x + normal.getLocalBounds().width))
	{
		if (mousePos.y> location.y && mousePos.y<(location.y + normal.getLocalBounds().height))
		{
			Locator::getSound().playSound(0, CLICK, false);
			return true;
        }
    }
	return false;
}

bool ui_Button::update (sf::Time deltaTime)
{
	if(isPushed)
	{
		if(delayPush <= sf::seconds(0.0f))//reset button
		{
			delayPush = delay;
			return true;
		}
		else
		{delayPush = delayPush - deltaTime;}
	}
	return false;
}

void ui_Button::setState(bool currentState) 
{
	isPushed = currentState;

    /*if (isPushed) 
	{currentSpr = &normal;}
	else
	{currentSpr = &clicked;}*/
}

void ui_Button::tog()
{
	if (isPushed)
	{
		isPushed = false;
		return;
	}
	isPushed = true;
}
void ui_Button::setSprite(bool newState)
{
	isPushed = newState;
	/*if (newState)
	{
		currentSpr = &clicked;
		return;
	}
	currentSpr = &normal;*/
}

void ui_Button::setText(std::string text){this->text.setString(text);}

bool ui_Button::getState(){return isPushed;}

sf::Sprite&  ui_Button::getSprite() 
{
	if (!isPushed)
	{return normal;}

    return clicked;
}

sf::Text& ui_Button::getText(){return text;}