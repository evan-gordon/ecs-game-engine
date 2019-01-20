
#include "Null_SoundService.h"

Null_SoundService::Null_SoundService() :AbsSoundService(){}
//null so all functions do nothing xD
Null_SoundService::~Null_SoundService(){}

void Null_SoundService::setVolume(float v){}

void Null_SoundService::setVolume(const Arguments& arg){}

void Null_SoundService::playSong(const SongName& song) {}

void Null_SoundService::playPlaylist(const Playlist& name) {}

void Null_SoundService::stopSong() {}

void Null_SoundService::updateSong() {}

void Null_SoundService::playSound(const Arguments& arg){}

void Null_SoundService::playSound(unsigned int id, const SfxName& name, bool loop){}

void Null_SoundService::stopSound(std::string s){}

void Null_SoundService::stopAllSounds(){}

void Null_SoundService::pauseAllSounds(){}

void Null_SoundService::unpauseAllSounds(){}

void Null_SoundService::update(sf::Vector2f playerPos){}