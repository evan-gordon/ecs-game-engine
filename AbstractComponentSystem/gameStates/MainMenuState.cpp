//Evan Gordon

#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont):IsState(window, gameEvent, gameFont),
		localPosition(sf::Vector2i(0, 0)), clicked(false), countDown(false), deltaTime(sf::Time::Zero)					
{
	if(!background.loadFromFile("images/mainMenuFinal.png"))
	{throw(42);}
	if(!menuButton.loadFromFile("images/menuButton.png"))
	{throw(42);}
	if(!menuButtonPressed.loadFromFile("images/menuButtonPressed.png"))
	{throw(42);}
	if(!settingsIconText.loadFromFile("images/settingsicon.png"))
	{throw(42);}
	mainMenuBackground.setTexture(background);
	mapMaker = ui_Button(menuButton, menuButtonPressed, std::string("Map Maker"), sf::Vector2f(100.0f, 580.0f), *gameFont, sf::seconds(1.0/2.0f));
	playGame = ui_Button(menuButton, menuButtonPressed, std::string("Play!"), sf::Vector2f(350.0f, 580.0f), *gameFont, sf::seconds(1.0/2.0f));
	settings = ui_Button(settingsIconText, settingsIconText, std::string(""), sf::Vector2f(1212.0f, 580.0f), *gameFont, sf::seconds(1.0/2.0f));
}

void MainMenuState::initialize()
{
	window->setMouseCursorVisible(true);
	gameTime.restart();
	mapMaker.setSprite(false);
	playGame.setSprite(false);
	settings.setSprite(false);
	mapMaker = ui_Button(menuButton, menuButtonPressed, std::string("Map Maker"), sf::Vector2f(100.0f, 580.0f), *gameFont, sf::seconds(1.0 / 2.0f));
	playGame = ui_Button(menuButton, menuButtonPressed, std::string("Play!"), sf::Vector2f(350.0f, 580.0f), *gameFont, sf::seconds(1.0 / 2.0f));
	settings = ui_Button(settingsIconText, settingsIconText, std::string(""), sf::Vector2f(1212.0f, 580.0f), *gameFont, sf::seconds(1.0 / 2.0f));
}

StateType MainMenuState::update()
{
	if (Locator::getConsoleUI().getCanDraw())
	{Locator::getConsoleUI().readEventLog();}

	deltaTime = gameTime.restart() + sf::seconds(1.0f/60.0f); 
	if(mapMaker.getState())
	{
		if(mapMaker.update(deltaTime))
		{return SelectMap;}
	}
	else if(playGame.getState())
	{
		if(playGame.update(deltaTime))
		{
		return SelectSave; //change to Play_Game?
		}
	}
	else if(settings.getState())
	{
		if(settings.update(deltaTime))
		{return Settings;}
	}
	return None;
}

void MainMenuState::draw()
{
	window->draw(mainMenuBackground);
	window->draw(settings.getSprite());
	window->draw(mapMaker.getSprite());
	window->draw(mapMaker.getText());
	window->draw(playGame.getSprite());
	window->draw(playGame.getText());

	if (Locator::getConsoleUI().getCanDraw())
	{Locator::getConsoleUI().draw(*window.get());}
}

bool MainMenuState::handleEvents()
{
	while (window->pollEvent(*gameEvent))
	{
		switch(gameEvent->type)
		{
			case sf::Event::Closed:
				window->close();
				return true;
			default:
				break;
		}
		if (Locator::getConsoleUI().getState() != CONSOLE)
		{
			if (gameEvent->type == sf::Event::MouseButtonPressed && gameEvent->mouseButton.button == sf::Mouse::Left)
			{
				localPosition = sf::Mouse::getPosition(*window);
				sf::Vector2f tempPosition((float)localPosition.x, (float)localPosition.y);
				if (mapMaker.checkIfClick(tempPosition))
				{
					mapMaker.setSprite(true);
				}
				if (playGame.checkIfClick(tempPosition))
				{
					playGame.setSprite(true);
				}
				if (settings.checkIfClick(tempPosition))
				{
					settings.setSprite(true);
				}
			}
			if (gameEvent->type == sf::Event::MouseButtonReleased && gameEvent->mouseButton.button == sf::Mouse::Left)
			{
				localPosition = sf::Mouse::getPosition(*window);
				sf::Vector2f tempPosition((float)localPosition.x, (float)localPosition.y);
				if (mapMaker.checkIfClick(tempPosition))
				{
					mapMaker.setState(true);
				}
				if (playGame.checkIfClick(tempPosition))
				{
					playGame.setState(true);
				}
				if (settings.checkIfClick(tempPosition))
				{
					settings.setState(true);
				}				
			}
			if (gameEvent->type == sf::Event::KeyReleased && gameEvent->key.code == sf::Keyboard::Tilde)
			{Locator::getConsoleUI().toggle();}
		}
		else
		{Locator::getConsoleUI().handleEvents(gameEvent);}
	}
	return false;
}

MainMenuState::~MainMenuState(){}

