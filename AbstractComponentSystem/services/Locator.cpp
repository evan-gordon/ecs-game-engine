
#include "Locator.h"

void Locator::init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
{
	consoleLog = std::shared_ptr<CManager>(new CManager());
	consoleLogUI = UIConsole(font, *window.get(), consoleLog);
	soundService = std::make_unique<SoundService>();
	consoleLog->console.setDefaultCommand(std::bind(&CManager::invalidCommand, std::ref(*consoleLog.get()), std::placeholders::_1));
	consoleLog->console.setCommand("playsound", std::bind(static_cast<void (AbsSoundService::*)(const Arguments&)>(&AbsSoundService::playSound), std::ref(*soundService.get()), std::placeholders::_1));
	consoleLog->console.setCommand("setvolume", std::bind(static_cast<void (AbsSoundService::*)(const Arguments&)>(&AbsSoundService::setVolume), std::ref(*soundService.get()), std::placeholders::_1));
	consoleLog->console.setCommand("togglesoundlog", std::bind(&Locator::toggleSoundLogging));
}//init all services to null versions

void Locator::setSound(AbsSoundService* newServ){soundService = std::unique_ptr<AbsSoundService>(newServ);}

AbsSoundService& Locator::getSound(){return *(soundService.get());}

void Locator::toggleSoundLogging()
{
	auto currSService = dynamic_cast<SoundDecorator*>(soundService.get());
	if (currSService == NULL)//logging disabled case
	{
		soundService = std::make_unique<SoundDecorator>(std::move(soundService));
		consoleLog->console.setCommand("playsound", std::bind(static_cast<void (AbsSoundService::*)(const Arguments&)>(&AbsSoundService::playSound), std::ref(*soundService.get()), std::placeholders::_1));
	}//more cases for when concrete type is added?
	else
	{
		auto temp = currSService->unwrap();
		soundService.reset();
		soundService = std::move(temp);
		consoleLog->console.setCommand("playsound", std::bind(static_cast<void (AbsSoundService::*)(const Arguments&)>(&AbsSoundService::playSound), std::ref(*soundService.get()), std::placeholders::_1));
	}
}

UIConsole& Locator::getConsoleUI()
{
	return consoleLogUI;
}

CManager& Locator::getConsole()
{
	return *consoleLog.get();
}

//initilization of services
std::shared_ptr<CManager> Locator::consoleLog = std::shared_ptr<CManager>(new CManager());
UIConsole Locator::consoleLogUI = UIConsole(consoleLog);
std::unique_ptr<AbsSoundService> Locator::soundService = NULL;
