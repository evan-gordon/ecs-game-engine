#include "SoundService.h"

SoundService::SoundService() : AbsSoundService()
{}

void SoundService::setVolume(float v)
{
	volume = v;
	if (volume < 0.f) { volume = 0.f; }
	else if (volume > 100.f) { volume = 100.f; }
	currSong.setVolume(volume);
	//TODO change components data structure, something iterable
}

void SoundService::setVolume(const Arguments& arg)
{
	setVolume(arg.floats[0]);
}

void SoundService::playSong(const SongName& song) 
{
	state = SONG;
	currSong.openFromFile(songList[song]);
	currSong.setVolume(volume);
	currSong.setPlayingOffset(sf::seconds(0.5));
	play();
}

void SoundService::playPlaylist(const Playlist& name) 
{
	state = PLAYLIST;
	currPlaylist = name;
	playlistIt = playlists[name].begin();
	currSong.openFromFile(*playlistIt);
	currSong.setVolume(volume);
	currSong.setPlayingOffset(sf::seconds(0.5));
	play();
}

void SoundService::stopSong() 
{
	state = STOPPED;
	currSong.stop();
}

void SoundService::updateSong() 
{
	if (currSong.getStatus() == sf::SoundSource::Status::Stopped)
	{
		if (state != PAUSED)
		{
			if (state == PLAYLIST)
			{
				playlistIt++;
				if (playlistIt == playlists[currPlaylist].end())
				{
					playlistIt = playlists[currPlaylist].begin();
				}
				currSong.openFromFile(*playlistIt);
				currSong.setVolume(volume);
				currSong.setPlayingOffset(sf::seconds(0.5));
				play();
			}
			else//restart song
			{
				currSong.play();
			}
		}
	}
}

void SoundService::playSound(const Arguments& arg)
{
	//playSound(arg.strings[0], false);//TODO
}

void SoundService::playSound(unsigned int id, const SfxName& name, bool loop)
{
	clearStoppedSounds();
	if (components.size() <= 200)
	{
		if (soundBuffer.find(name) != soundBuffer.end())//sfx exits
		{
			for (auto it = idMap[id].begin(); it != idMap[id].end(); ++it)
			{if (it->name == name) { return; }}//return if that character is already playing this sound
			
			if (idMap.find(id) == idMap.end())
			{
				idMap.insert(std::make_pair(id, std::vector<Sfx>()));
			}

			auto r = idMap[id].insert(idMap[id].begin(), Sfx(name, sf::Sound(soundBuffer[name])));
			r->sound.setLoop(false);
			r->sound.play();
			components.push(std::make_pair(id, r));

			//components.back().setPosition();//add later, positional code for sfx
			//components.back().set
			//const sf::Vector2f& tempPos = worldObjectManager.getLocationf(ID);
			//soundList[soundList.size() - 1].setPosition(tempPos.x, tempPos.y, 0);
			//soundList[soundList.size() - 1].play();
		}
	}
}

void SoundService::clearStoppedSounds()
{
	while (components.size() != 0 && components.front().second->sound.getStatus() == sf::Sound::Stopped)
	{
		idMap[components.front().first].erase(components.front().second);//might have problems
		components.pop();
	}
}

void SoundService::stopSound(std::string s)
{

}

void SoundService::stopAllSounds()
{

}

void SoundService::pauseAllSounds()
{

}

void SoundService::unpauseAllSounds()
{

}

void SoundService::update(sf::Vector2f playerPos)//update position of listener during game
{
	sf::Vector3f temp(playerPos.x, playerPos.y, 0);
	listener.setPosition(temp);
}

SoundService::~SoundService()
{

}