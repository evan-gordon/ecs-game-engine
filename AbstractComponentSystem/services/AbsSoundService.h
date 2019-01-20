#ifndef ABSSOUNDSERVICE_H
#define ABSSOUNDSERVICE_H

#include <queue>
#include <utility>
#include <string>
#include <map>
#include <sstream>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "../console/Arguments.h"

enum Playlist{CHEERY};//add more playlists
enum SongState{PLAYLIST, SONG , STOPPED, PAUSED};
enum SongName {LIFEOFRILEY, FRETLESS, CAREFREE};

enum SfxName{CLICK, TELE, GRASSWALK, STONESTEP};

//container for data related to a sfx
struct Sfx
{
	SfxName name;
	sf::Sound sound;

	Sfx::Sfx(SfxName name, sf::Sound sound):
		name(name), sound(sound)
	{}
};

class AbsSoundService
{
public:
	AbsSoundService() :listener(), playerID(0), volume(30), soundBuffer(), components()
	{
		soundBuffer.insert(std::make_pair(CLICK, sf::SoundBuffer()));
		if (!soundBuffer[CLICK].loadFromFile("audio/sounds/click.ogg")){throw(42);}

		soundBuffer.insert(std::make_pair(TELE, sf::SoundBuffer()));
		if (!soundBuffer[TELE].loadFromFile("audio/sounds/teleport.ogg")){throw(42);}

		soundBuffer.insert(std::make_pair(GRASSWALK, sf::SoundBuffer()));
		if (!soundBuffer[GRASSWALK].loadFromFile("audio/sounds/grasswalk.ogg")){throw(42);}

		soundBuffer.insert(std::make_pair(STONESTEP, sf::SoundBuffer()));
		if (!soundBuffer[STONESTEP].loadFromFile("audio/sounds/stonestep.ogg")){throw(42);}

		//load music files
		songList.insert(std::make_pair(LIFEOFRILEY, "audio/music/Life_of_Riley.ogg"));
		songList.insert(std::make_pair(FRETLESS, "audio/music/Fretless.ogg"));
		songList.insert(std::make_pair(CAREFREE, "audio/music/Carefree.ogg"));

		playlists.insert(std::make_pair(CHEERY, std::vector<std::string>()));
		playlists[CHEERY].insert(playlists[CHEERY].end(), { "audio/music/Life_of_Riley.ogg",
			"audio/music/Fretless.ogg" , "audio/music/Carefree.ogg" });

		currSong.setVolume((float)volume);
		currSong.setPlayingOffset(sf::seconds(0.5));
	}
	virtual ~AbsSoundService(){}

	virtual void setVolume(float v) = 0;
	virtual void setVolume(const Arguments& arg) = 0;
	virtual void playSound(const Arguments& arg) = 0;

	virtual void playSong(const SongName& song) = 0;
	virtual void playPlaylist(const Playlist& name) = 0;
	virtual void stopSong() = 0;
	virtual void updateSong() = 0;

	virtual void playSound(unsigned int id, const SfxName& name, bool loop) = 0;
	virtual void stopSound(std::string s) = 0;
	virtual void stopAllSounds() = 0;
	virtual void pauseAllSounds() = 0;
	virtual void unpauseAllSounds() = 0;
	virtual void update(sf::Vector2f playerPos) = 0;//update position of listener during game

	float getVolume()
	{
		return volume;
	}

	void play()
	{
		currSong.play();
	}

protected:
	float volume;
	SongState state;
	Playlist currPlaylist;
	unsigned int playerID;
	const int MAX_SOUNDS = 255;//255 sounds and 1 song are max
	sf::Listener listener;
	sf::Music currSong;
	std::map<SfxName, sf::SoundBuffer> soundBuffer;
	std::vector<std::string>::iterator playlistIt;
	std::map<SongName, std::string> songList;
	std::map<Playlist, std::vector<std::string>> playlists;

	std::map<unsigned int, std::vector<Sfx>> idMap;//this stores it all, then queue is for deleting it
	std::queue<std::pair<unsigned int, std::vector<Sfx>::iterator>> components;//id of caller, pointer to element in maps vector
};
#endif
