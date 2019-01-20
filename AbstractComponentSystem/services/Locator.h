#ifndef LOCATOR_H
#define LOCATOR_H

#include <SFML/Graphics.hpp>

#include "AbsSoundService.h"
#include "Null_SoundService.h"
#include "SoundService.h"
#include "../ui/UIConsole.h"
#include "../console/CManager.h"
#include "SoundDecorator.h"

#include <memory>

//no constructor or destructor... for now
//this is my service locator class, it is going to be used to give global access to certain features that need global access,
//current uses are the audio service, and logging system, probably also the console as well down the line, and maybe even moving all ui elements up here <- could potentially clean up code really well
class Locator
{
public:
	static void init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font);

	//register funcs for each service
	static void setSound(AbsSoundService* newServ);
	static AbsSoundService& getSound();
	static void toggleSoundLogging();

	static UIConsole& getConsoleUI();
	static CManager& getConsole();
	//getter for each

	//switch function, for switching between logging and no logging function, use decorator for this

private:
	//actual services
	static std::shared_ptr<CManager> consoleLog;
	static UIConsole consoleLogUI;
	static std::unique_ptr<AbsSoundService> soundService;
	//null service objs?
};
#endif
