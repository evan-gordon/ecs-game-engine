//Evan Gordon

#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "../pugixml.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "../g_Functions.h"
#include "../services/Locator.h"
#include "IsState.h"

class SettingsState:public IsState
{
public:
	SettingsState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont);
	~SettingsState();

	void initialize();
	StateType update();
	void draw();
	bool handleEvents();
	bool canMove(bool moveDown);
	void moveList(bool moveDown);
	void setScale();
	void inputToText();
	void readFile();
	void saveFile();

private:
	float calcVolumeRange();

	bool exit, editingInput;
	int selectionNumber;

	pugi::xml_document inputFile;
	pugi::xml_node node;
	sf::Text info, soundTxt;
	sf::Texture selectTexture;
	sf::Sprite selectLeft, selectRight;
	sf::Keyboard::Key up, down, left, right, select;
	sf::RectangleShape slider, sliderBar;
	std::vector<std::pair<sf::Text, sf::Text>> inputList;
	//later add another vector for things like volume, resolution, and other settings
};

#endif