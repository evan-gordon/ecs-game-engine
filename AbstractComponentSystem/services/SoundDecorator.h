
#ifndef SOUNDDECORATOR_H
#define SOUNDDECORATOR_H

#include "AbsSoundService.h"
#include "Locator.h"
#include "../console/CManager.h"

#include <memory>

//This class maintains a reference to the non logging version of the sound service
//this class will extend off of the base class and add logging abilities to it
class SoundDecorator: public AbsSoundService
{
public:
	SoundDecorator(std::unique_ptr<AbsSoundService>&& sService);
	~SoundDecorator();

	std::unique_ptr<AbsSoundService> unwrap();
	void stopSound(std::string s);
	void setVolume(const Arguments& arg);

	void playSong(const SongName& song);
	void playPlaylist(const Playlist& name);
	void stopSong();
	void updateSong();

	void playSound(const Arguments& arg);
	void playSound(unsigned int id, const SfxName& name, bool loop);
	void setVolume(float v);
	void stopAllSounds();
	void pauseAllSounds();
	void unpauseAllSounds();
	void update(sf::Vector2f playerPos);

private:
	std::unique_ptr<AbsSoundService> soundService;
};
#endif