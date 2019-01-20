//Evan Gordon

#include "SettingsState.h"


SettingsState::SettingsState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Event> gameEvent, std::shared_ptr<sf::Font> gameFont) :IsState(window, gameEvent, gameFont),
exit(false), editingInput(false), selectionNumber(0), info("Press Esc to Save and Exit", *gameFont, 26), soundTxt("Volume:", *gameFont, 12)
{
	info.setOrigin(info.getLocalBounds().width / 2.0f, 0);
	info.setPosition(window->getSize().x / 2.0f, 100.0f);
	if (!selectTexture.loadFromFile("images/mapSelector.png")){ throw(42); }

	selectLeft = sf::Sprite(selectTexture, sf::IntRect(0, 0, 5, selectTexture.getSize().y));
	selectRight = sf::Sprite(selectTexture, sf::IntRect(selectTexture.getSize().x - 5, 0, 5, selectTexture.getSize().y));
	selectLeft.setOrigin(5, selectLeft.getTextureRect().height / 2.0f);
	selectRight.setOrigin(0, selectRight.getTextureRect().height / 2.0f);
	selectLeft.setPosition(-50, -50); //no valid position until inputs are loaded
	selectRight.setPosition(-50, -50);

	slider.setFillColor(sf::Color(66, 134, 244));
	slider.setSize(sf::Vector2f(12, 24));
	slider.setPosition(window->getSize().x / 2.f + calcVolumeRange(), window->getSize().y / 2.0f + 150.f);
	sliderBar.setFillColor(sf::Color(160, 160, 160));
	sliderBar.setSize(sf::Vector2f(128, 4));
	sliderBar.setPosition(window->getSize().x / 2.f + 35.0f, window->getSize().y / 2.0f + 159.f);


	soundTxt.setPosition(window->getSize().x / 2.f - 140.0f, window->getSize().y / 2.0f + 150.f);
}

void SettingsState::initialize()
{
	exit = false;
	selectionNumber = 0;
	readFile();

	//setup menu
	std::pair<int, int> windowSize(window->getSize().x, window->getSize().y);
	for (size_t i = 0; i < inputList.size(); i++)
	{
		inputList[i].first.setOrigin(0, inputList[i].first.getLocalBounds().height / 2.0f);
		inputList[i].second.setOrigin(0, inputList[i].first.getLocalBounds().height / 2.0f);
		inputList[i].first.setPosition(windowSize.first / 2.0f - 140.0f, windowSize.second / 2.0f + (i * 50.0f));
		inputList[i].second.setPosition(windowSize.first / 2.0f + 90.0f, windowSize.second / 2.0f + (i * 50.0f));

		//set inputs
		if (inputList[i].first.getString() == "playerup")
		{
			up = stringToKeyboardKey(inputList[i].second.getString());
		}
		else if (inputList[i].first.getString() == "playerdown")
		{
			down = stringToKeyboardKey(inputList[i].second.getString());
		}
		else if (inputList[i].first.getString() == "playerleft")
		{
			left = stringToKeyboardKey(inputList[i].second.getString());
		}
		else if (inputList[i].first.getString() == "playerright")
		{
			right = stringToKeyboardKey(inputList[i].second.getString());
		}
		else if (inputList[i].first.getString() == "attack1")
		{
			select = stringToKeyboardKey(inputList[i].second.getString());
		}
	}
	selectLeft.setPosition(inputList[0].second.getPosition().x - 15.0f, windowSize.second / 2.0f);
	selectRight.setPosition(inputList[0].second.getPosition().x + inputList[0].second.getLocalBounds().width + 15.0f, windowSize.second / 2.0f);

	setScale();
}

StateType SettingsState::update()
{
	if (Locator::getConsoleUI().getCanDraw()) {Locator::getConsoleUI().readEventLog();}

	if (exit)//if exit is pressed, save file changes?
	{
		window->setMouseCursorVisible(true);
		saveFile();
		return Pop;
	}
	else
	{return None;}
}

void SettingsState::draw()
{
	window->draw(sliderBar);
	window->draw(slider);
	window->draw(soundTxt);

	window->draw(info);
	window->draw(selectLeft);
	window->draw(selectRight);
	for (int i = 0; i < (int)inputList.size(); i++)
	{
		if (i < (selectionNumber + 3) && i >(selectionNumber - 3))
		{
			window->draw(inputList[i].first);
			window->draw(inputList[i].second);
		}
	}

	if (Locator::getConsoleUI().getCanDraw())
	{Locator::getConsoleUI().draw(*window.get());}
}

bool SettingsState::handleEvents()
{
	while (window->pollEvent(*gameEvent))
	{
		if (gameEvent->type == sf::Event::Closed)
		{
			window->close();
			return true;
		}
		if (Locator::getConsoleUI().getState() != CONSOLE)
		{
			if (!editingInput && gameEvent->type == sf::Event::KeyReleased)
			{
				if (gameEvent->key.code == sf::Keyboard::Escape)//stop editing current settings
				{
					exit = true;
				}
				else if (gameEvent->type == sf::Event::KeyReleased && gameEvent->key.code == sf::Keyboard::Tilde)
				{
					Locator::getConsoleUI().toggle();
				}
				else if (gameEvent->key.code == select)
				{
					if (selectionNumber != (int)inputList.size())
					{
						editingInput = true;
						inputList[selectionNumber].second.setFillColor(sf::Color::Yellow);
					}
				}
				else if (gameEvent->key.code == up)//move up list
				{
					if (canMove(false))
					{
						moveList(false);
					}
				}
				else if (gameEvent->key.code == down)//move down list
				{
					if (canMove(true))
					{moveList(true);}
				}
				else if (gameEvent->key.code == left && selectionNumber == (int)inputList.size())
				{
					Locator::getSound().setVolume(Locator::getSound().getVolume() - 5);
					slider.setPosition(window->getSize().x / 2.f + calcVolumeRange(), slider.getPosition().y);
				}
				else if (gameEvent->key.code == right && selectionNumber == (int)inputList.size())
				{
					Locator::getSound().setVolume(Locator::getSound().getVolume() + 5);
					slider.setPosition(window->getSize().x / 2.f + calcVolumeRange(), slider.getPosition().y);
				}
			}
			else if (editingInput)
			{inputToText();}
		}
		else
		{Locator::getConsoleUI().handleEvents(gameEvent);}
	}
	return false;
}

void SettingsState::inputToText()
{
	if (gameEvent->type == sf::Event::TextEntered)//take raw text and turn it into the input
	{
		//take raw text and turn it into the input
		if ((gameEvent->text.unicode > 0x02B && gameEvent->text.unicode < 0x03C) || (gameEvent->text.unicode > 0x05A && gameEvent->text.unicode < 0x05E) ||
			gameEvent->text.unicode == 0x027 || gameEvent->text.unicode == 0x03D || (gameEvent->text.unicode > 0x060 && gameEvent->text.unicode < 0x07B))// basic alphabet
		{
			sf::String temp;
			temp = static_cast<char>(gameEvent->text.unicode);
			inputList[selectionNumber].second.setString(temp);
		}
		else if (gameEvent->text.unicode > 0x00B)
		{
			//space
			inputList[selectionNumber].second.setString("space");
		}//add in the rest on a later date. some weird error is showing up with detecting which key is pressed
		//else if(gameEvent->text.unicode > 0x009 )
		//{
		//	//tab
		//	inputList[selectionNumber].second.setString("tab");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::LShift )
		//{
		//	//lshift
		//	inputList[selectionNumber].second.setString("leftshift");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::LControl )
		//{
		//	//lcontrol
		//	inputList[selectionNumber].second.setString("leftcontrol");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::LAlt )
		//{
		//	//lalt
		//	inputList[selectionNumber].second.setString("leftalt");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::RShift )
		//{
		//	//rshift
		//	inputList[selectionNumber].second.setString("rightshift");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::RControl )
		//{
		//	//rcontrol
		//	inputList[selectionNumber].second.setString("rightcontrol");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::RAlt )
		//{
		//	//ralt
		//	inputList[selectionNumber].second.setString("rightalt");
		//}
		//else if(gameEvent->text.unicode > 0x008 )
		//{
		//	//backspace
		//	inputList[selectionNumber].second.setString("backspace");
		//}
		//else if(gameEvent->text.unicode > 0x085 )
		//{
		//	//enter
		//	inputList[selectionNumber].second.setString("return");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Home )
		//{
		//	//home
		//	inputList[selectionNumber].second.setString("home");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::PageUp )
		//{
		//	//pgup
		//	inputList[selectionNumber].second.setString("pgup");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::PageDown )
		//{
		//	//pgdown
		//	inputList[selectionNumber].second.setString("pgdn");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::End )
		//{
		//	//end
		//	inputList[selectionNumber].second.setString("end");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Insert )
		//{
		//	//insert
		//	inputList[selectionNumber].second.setString("insert");
		//}
		//else if(gameEvent->text.unicode > 0x07F )
		//{
		//	//insert
		//	inputList[selectionNumber].second.setString("delete");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num0 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("0");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num1 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("1");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num2 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("2");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num3 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("3");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num4 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("4");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num5 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("5");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num6 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("6");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num7 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("7");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num8 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("8");
		//}
		//else if(gameEvent->text.unicode > sf::Keyboard::Num9 )
		//{
		//	//num pad
		//	inputList[selectionNumber].second.setString("9");
		//}
		editingInput = false;
		inputList[selectionNumber].second.setFillColor(sf::Color::White);

		selectLeft.setPosition(inputList[selectionNumber].second.getPosition().x - 15.0f, window->getSize().y / 2.0f);
		selectRight.setPosition(inputList[selectionNumber].second.getPosition().x + inputList[selectionNumber].second.getLocalBounds().width + 15, window->getSize().y / 2.0f);
	}
}

bool SettingsState::canMove(bool moveDown)
{
	if (moveDown)
	{
		if ((selectionNumber + 1) <= (int)inputList.size() - 1 + 1){return true;}//the extra plus one is for sounds position
	}
	else
	{
		if ((selectionNumber - 1) >= 0){return true;}
	}
	return false;
}

void SettingsState::moveList(bool moveDown)
{
	if (moveDown)
	{
		selectionNumber++;
		if (selectionNumber != (int)inputList.size())
		{
			for (size_t i = 0; i < inputList.size(); i++)
			{
				inputList[i].first.setPosition(inputList[i].first.getPosition().x, inputList[i].first.getPosition().y - 50);
				inputList[i].second.setPosition(inputList[i].second.getPosition().x, inputList[i].second.getPosition().y - 50);
			}
		}
	}
	else
	{
		selectionNumber--;
		if (selectionNumber != (int)inputList.size() - 1)
		{
			for (size_t i = 0; i < inputList.size(); i++)
			{
				inputList[i].first.setPosition(inputList[i].first.getPosition().x, inputList[i].first.getPosition().y + 50);
				inputList[i].second.setPosition(inputList[i].second.getPosition().x, inputList[i].second.getPosition().y + 50);
			}
		}
	}
	if (selectionNumber != (int)inputList.size())
	{
		setScale();
	}
	//move cursor size
	if (selectionNumber == (int)inputList.size())
	{
		selectLeft.setPosition(window->getSize().x / 2.f + 20, window->getSize().y / 2.0f + 160.f);
		selectRight.setPosition(window->getSize().x / 2.f + 180, window->getSize().y / 2.0f + 160.f);
	}
	else
	{
		selectLeft.setPosition(inputList[selectionNumber].second.getPosition().x - 15, window->getSize().y / 2.0f);
		selectRight.setPosition(inputList[selectionNumber].second.getPosition().x + inputList[selectionNumber].second.getLocalBounds().width + 15.0f, window->getSize().y / 2.0f);
	}
}

void SettingsState::setScale()
{
	for (size_t i = 0; i < inputList.size(); i++)
	{
		if (i == selectionNumber)
		{
			inputList[i].first.setScale(1.0f, 1.0f);
			inputList[i].second.setScale(1.0f, 1.0f);
		}
		else if (i == (selectionNumber + 1) || i == (selectionNumber - 1))
		{
			inputList[i].first.setScale(0.8f, 0.8f);
			inputList[i].second.setScale(0.8f, 0.8f);
		}
		else if (i == (selectionNumber + 2) || i == (selectionNumber - 2))
		{
			inputList[i].first.setScale(0.6f, 0.6f);
			inputList[i].second.setScale(0.6f, 0.6f);
		}
	}
}

void SettingsState::readFile()
{
	window->setMouseCursorVisible(false);
	inputList.clear();
	if (!inputFile.load_file("xml/input.xml"))
	{
		try
		{
			throw;
		}
		catch (std::exception)
		{
			Locator::getConsole().log("serialize failed to read in .xml input prefab file. \n");
		}
	}

	//read in input pairs
	node = inputFile.child("input");
	for (auto inputName = node.first_child(); inputName; inputName = inputName.next_sibling())
	{
		inputList.push_back(std::make_pair<sf::Text, sf::Text>(sf::Text(inputName.name(), *gameFont, 14), sf::Text(inputName.child("key").text().as_string(), *gameFont, 14)));
	}
}

void SettingsState::saveFile()
{
	pugi::xml_node temp;
	for (size_t i = 0; i < inputList.size(); i++)
	{
		std::string name = inputList[i].first.getString();
		temp = node.child(name.c_str());
		if (temp.child("key").text().as_string() != inputList[i].second.getString())
		{
			std::string newKey = inputList[i].second.getString();
			temp.child("key").text().set(newKey.c_str());
		}
	}
	inputFile.save_file("xml/input.xml");
}

//34 - 156 range
float SettingsState::calcVolumeRange()
{
	if (Locator::getSound().getVolume() <= 0.f) { return 34.f; }

	return ((156.f - 34.f) * (Locator::getSound().getVolume() / 100.f)) + 34.f;
}

SettingsState::~SettingsState(){}