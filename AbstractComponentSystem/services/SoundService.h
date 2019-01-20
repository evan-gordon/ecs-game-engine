//Evan Gordon

#ifndef SOUNDSERVICE_H
#define SOUNDSERVICE_H

#include <SFML/Audio.hpp>

#include "../console/Arguments.h"
#include "AbsSoundService.h"

class SoundService: public AbsSoundService
{
public:
	SoundService();
	~SoundService();
	
	void setVolume(float v);
	void setVolume(const Arguments& arg);

	void playSong(const SongName& song);
	void playPlaylist(const Playlist& name);
	void stopSong();
	void updateSong();

	void playSound(const Arguments& arg);
	void playSound(unsigned int id, const SfxName& name, bool loop);
	void stopSound(std::string s);
	void stopAllSounds();
	void pauseAllSounds();
	void unpauseAllSounds();
	void update(sf::Vector2f playerPos);//update position of listener during game

private:
	void clearStoppedSounds();
};

#endif