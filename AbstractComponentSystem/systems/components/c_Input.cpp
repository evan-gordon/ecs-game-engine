//Evan Gordon

#include "c_Input.h"

c_Input::c_Input(sf::Event::EventType type, sf::Keyboard::Key key):
	keyboardInput(key), eventType(type)
{}
c_Input::c_Input(sf::Event::EventType type, sf::Mouse::Button button):
	eventType(type), mouseInput(button)
{}

c_Input::~c_Input() {}