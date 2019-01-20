
#include "SoundDecorator.h"

//once i move the log and console code up to the service locator, then add logging code to this
SoundDecorator::SoundDecorator(std::unique_ptr<AbsSoundService>&& sService) :AbsSoundService(), soundService(std::move(sService))
{}


std::unique_ptr<AbsSoundService> SoundDecorator::unwrap()
{
	return std::move(soundService);
}

void SoundDecorator::stopSound(std::string s)
{
	Locator::getConsole().log("Stopping " + s + ".");
	soundService->stopSound(s);
}
void SoundDecorator::playSound(unsigned int id, const SfxName& name, bool loop)
{
	Locator::getConsole().log("Playing " + std::to_string(name) + ".");
	soundService->playSound(id, name, loop);
}

void SoundDecorator::playSound(const Arguments& arg)
{
	Locator::getConsole().log("Volume " + arg.strings[0] + ".");
	soundService->playSound(arg);
}

void SoundDecorator::setVolume(const Arguments& arg)
{
	Locator::getConsole().log("Playing " + arg.strings[0] + ".");
	soundService->setVolume(arg);
}

void SoundDecorator::setVolume(float v)
{
	Locator::getConsole().log("Volume " + std::to_string(v) + ".");
	soundService->setVolume(v);
}

void SoundDecorator::playSong(const SongName& song) 
{
	Locator::getConsole().log("Playing song " + std::to_string(song) + ".");
	soundService->playSong(song);
}

void SoundDecorator::playPlaylist(const Playlist& name) 
{
	Locator::getConsole().log("Playing playlist " + std::to_string(name) + ".");
	soundService->playPlaylist(name);
}

void SoundDecorator::stopSong() 
{
	Locator::getConsole().log("Stopping song");
	soundService->stopSong();
}

void SoundDecorator::updateSong() 
{
	Locator::getConsole().log("Updating song");
	soundService->updateSong();
}

void SoundDecorator::stopAllSounds()
{
	Locator::getConsole().log("Stopping all sounds.");
	soundService->stopAllSounds();
}

void SoundDecorator::pauseAllSounds()
{
	Locator::getConsole().log("Pausing Sounds.");
	soundService->pauseAllSounds();
}

void SoundDecorator::unpauseAllSounds()
{
	Locator::getConsole().log("Resuming Sounds.");
	soundService->unpauseAllSounds();
}

void SoundDecorator::update(sf::Vector2f playerPos)
{
	Locator::getConsole().log("Updating listener Loc to" + std::to_string(playerPos.x) + "," + std::to_string(playerPos.y) + ".");
	soundService->update(playerPos);
}

SoundDecorator::~SoundDecorator(){}