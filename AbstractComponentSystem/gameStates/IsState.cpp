//Evan Gordon
//game state code, for both basic state and state stack basis was drawn from information on http://gamedevelopment.tutsplus.com/

#include "IsState.h"

IsState::IsState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont) 
	:window(window), gameEvent(gameEvent), gameFont(gameFont)
{}

void IsState::initialize() {}

StateType IsState::update() {return None;}

void IsState::draw() {}

bool IsState::handleEvents() {return false;}


IsState::~IsState(){}
