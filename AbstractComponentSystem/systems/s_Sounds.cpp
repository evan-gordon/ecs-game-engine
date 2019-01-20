#include "s_Sounds.h"

s_Sounds::s_Sounds(s_WorldObject& worldObjectManager, const unsigned int& playerID):
listener(), worldObjectManager(worldObjectManager), playerID(playerID)
{
	soundBuffer.insert(std::pair<std::string, sf::SoundBuffer>("teleport", sf::SoundBuffer()));
	if (!soundBuffer["teleport"].loadFromFile("audio/sounds/teleport.ogg"))
	{
		throw(42);
	}
	/*soundBuffer.insert(std::pair<std::string, sf::SoundBuffer>("grasswalk", sf::SoundBuffer()));
	if (!soundBuffer["grasswalk"].loadFromFile("audio/sounds/grasswalk.ogg"))
	{
		throw(42);
	}*/
	soundBuffer.insert(std::pair<std::string, sf::SoundBuffer>("stonestep", sf::SoundBuffer()));
	if (!soundBuffer["stonestep"].loadFromFile("audio/sounds/stonestep.ogg"))
	{
		throw(42);
	}
}

void s_Sounds::update()//for use only in game logic
{
	auto playerLoc = worldObjectManager.getLocationf(playerID);
	listener.setPosition(sf::Vector3f(playerLoc.x, playerLoc.y, 0));
	//add facing later?
}

void s_Sounds::addComponent(unsigned int ID)
{
}

void s_Sounds::removeComponent(unsigned int ID)
{
}

void s_Sounds::playSound(unsigned int ID, SfxName s)//add argument bool for turning on looping?
{
	Locator::getSound().playSound(ID, s, false);

	//std::vector<sf::Sound>& soundList = components[ID];
	//for (auto it = soundList.begin(); it != soundList.end(); it++)//clear up any elements that are done playing
	//{
	//	if (it->getStatus() == sf::Sound::Status::Stopped)
	//	{it = soundList.erase(it);}
	//}
	//if ((int)soundList.size() <= MAX_SOUNDS)
	//{
	//	soundList.push_back(sf::Sound(soundBuffer[s]));
	//	const sf::Vector2f& tempPos = worldObjectManager.getLocationf(ID);
	//	soundList[soundList.size() - 1].setPosition(tempPos.x, tempPos.y, 0);
	//	soundList[soundList.size() - 1].play();
	//}
	//if all sounds are being used then dont play new sound it
}

s_Sounds::~s_Sounds(){}