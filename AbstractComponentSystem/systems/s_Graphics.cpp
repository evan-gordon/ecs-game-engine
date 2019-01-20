//Evan Gordon
#include "s_Graphics.h"

s_Graphics::s_Graphics(s_WorldObject& worldObjects, sf::View& gameView, std::shared_ptr<sf::RenderWindow> window)
	:worldObjectManager(worldObjects), gameView(gameView), window(window)
{
	textures.insert(std::make_pair("images/weapons.png", sf::Texture()));
	if (!textures["images/weapons.png"].loadFromFile("images/weapons.png"))
	{
		Locator::getConsole().log("weapons.png could not be loaded\n");
		throw(42);
	}
	textures.insert(std::make_pair("images/king.png", sf::Texture()));
	if (!textures["images/king.png"].loadFromFile("images/king.png"))
	{
		Locator::getConsole().log("images/king.png could not be loaded\n");
		throw(42);
	}
	textures.insert(std::make_pair("images/apple.png", sf::Texture()));
	if (!textures["images/apple.png"].loadFromFile("images/apple.png"))
	{
		Locator::getConsole().log("images/apple.png could not be loaded\n");
		throw(42);
	}
	textures.insert(std::make_pair("images/portal.png", sf::Texture()));
	if (!textures["images/portal.png"].loadFromFile("images/portal.png"))
	{
		Locator::getConsole().log("images/portal.png could not be loaded\n");
		throw(42);
	}
	textures.insert(std::make_pair("images/slime.png", sf::Texture()));
	if (!textures["images/slime.png"].loadFromFile("images/slime.png"))
	{
		Locator::getConsole().log("images/slime.png could not be loaded\n");
		throw(42);
	}
	if (!textures["images/testlimbs.png"].loadFromFile("images/testlimbs.png"))
	{
		Locator::getConsole().log("images/testlimbs.png could not be loaded\n");
		throw(42);
	}
}

void s_Graphics::update()
{
	window->setView(gameView);
	worldObjectManager.sorter.sort();
	auto list = worldObjectManager.sorter.getList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		auto& temp = components[it->first];
		if ((it->second.position.x != temp.sprite.getPosition().x) || (it->second.position.y != temp.sprite.getPosition().y))//if postion has been moved, update sprite location
		{
			temp.sprite.setPosition(it->second.position.x, it->second.position.y);
			if (it->first == 1)//this assumes that the players id is 1. special case for updating players position
			{
				//const sf::Vector2f tPos(worldObjectManager.sorter.find(1)->position);
				gameView.setCenter(it->second.position.x, it->second.position.y);
			}
		}
		window->draw(components[it->first].sprite);
	}
}

sf::Vector2f s_Graphics::getUpperLeftPos(unsigned int ID)
{
	return sf::Vector2f(worldObjectManager.getLocationf(ID).x - components.at(ID).sprite.getOrigin().x, 
		worldObjectManager.getLocationf(ID).y - components.at(ID).sprite.getOrigin().y);
}

void s_Graphics::addComponent(unsigned int ID, c_Graphics& graphic)
{
	components.insert(std::pair<unsigned int, c_Graphics>(ID, graphic));
	components[ID].sprite.setPosition(worldObjectManager.sorter.find(ID)->position);
}

sf::Texture *s_Graphics::getSprite(std::string name){return &textures[name];}

void s_Graphics::removeComponent(unsigned int ID){components.erase(ID);}

void s_Graphics::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	pugi::xml_node curr = parent.append_child("graphics");
	curr.append_child("texture");
	curr.append_child("x");
	curr.append_child("y");
	curr.append_child("width");
	curr.append_child("height");
	curr.append_child("originx");
	curr.append_child("originy");
	curr.child("texture").append_child(pugi::node_pcdata).set_value(components[ID].textName.c_str());
	std::string temp = std::to_string(components[ID].sprite.getTextureRect().left);
	curr.child("x").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].sprite.getTextureRect().top);
	curr.child("y").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].sprite.getTextureRect().width);
	curr.child("width").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].sprite.getTextureRect().height);
	curr.child("height").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].sprite.getOrigin().x);
	curr.child("originx").append_child(pugi::node_pcdata).set_value(temp.c_str());
	temp = std::to_string(components[ID].sprite.getOrigin().y);
	curr.child("originy").append_child(pugi::node_pcdata).set_value(temp.c_str());
}

s_Graphics::~s_Graphics() {}