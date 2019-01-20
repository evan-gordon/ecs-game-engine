//Evan Gordon

#ifndef S_SOUNDS_H
#define S_SOUNDS_H

#include <map>
#include <string>
#include <memory>
#include <vector>

#include <SFML/Audio.hpp>

#include "s_WorldObject.h"
#include "../services/Locator.h"

class s_Sounds
{
public:
	const int MAX_SOUNDS = 255;//255 sounds and 1 song are max
	sf::Listener listener;
	unsigned int playerID;
	std::map<std::string, sf::SoundBuffer> soundBuffer;
	std::map<unsigned int, std::vector<sf::Sound>> components;

	s_WorldObject& worldObjectManager;//needed for fetching position of sounds being played

	s_Sounds(s_WorldObject& worldObjectManager, const unsigned int& playerID);
	~s_Sounds();

	void update();
	//void readFromFile(unsigned int ID);//not sure if any form of saving will be needed
	void addComponent(unsigned int ID);
	void removeComponent(unsigned int ID);
	//void savetoFile(pugi::xml_node parent);

	void playSound(unsigned int ID, SfxName s);
};

#endif