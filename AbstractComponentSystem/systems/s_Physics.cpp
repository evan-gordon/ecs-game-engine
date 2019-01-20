//Evan Gordon 

#include "s_Physics.h"

s_Physics::s_Physics(s_WorldObject& worldObjects, s_Graphics& graphicsManager, s_Action& inputManager, s_Map& gameMap, sf::Time& deltaTime)
:worldObjectManager(worldObjects), deltaTime(deltaTime), inputManager(inputManager), graphicsManager(graphicsManager), gameMap(gameMap)
{}

void s_Physics::update()
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		c_Action& temp = inputManager.getAction(it->first);
		updatePhysics(it->first, it->second, temp);
	}
}

void s_Physics::updatePhysics(unsigned int ID, c_Physics& curr, c_Action& action)
{
	//sf::Vector2f newAcc(55.0f * std::cos((action.lookAngle * M_PI) / 180.0f), 55.0f * std::sin((action.lookAngle * M_PI) / 180.0f));
	//when looking to optimize code use, sin and cos lookup table,
	//https://stackoverflow.com/questions/2479517/is-trigonometry-computationally-expensive
	float aDecel = 0.92f, friction = 0.9f, acceleration = 75.0f, vDecel = 0.85f;//these will need to move to other places later in development
	if (action.lookAngle != 90 && action.lookAngle != 270 && action.lookAngle >= 0)
	{

		curr.acc.x = calcVectorX(acceleration, action.lookAngle);//use newAcc cos
		curr.velocity.x += curr.acc.x * deltaTime.asSeconds() * friction; //v += acc - friction*v
		if (curr.velocity.x > curr.maxVelocity){ curr.velocity.x = curr.maxVelocity; }
	}
	else
	{
		curr.acc.x *= aDecel;
		curr.velocity.x *= vDecel; //v += acc - friction*v
	}

	if (action.lookAngle != 0 && action.lookAngle != 180 && action.lookAngle >= 0)
	{
		curr.acc.y =  calcVectorY(acceleration, action.lookAngle);//use newAcc cos
		curr.velocity.y += curr.acc.y * deltaTime.asSeconds() * friction; //v += acc - friction*v
		if (curr.velocity.y > curr.maxVelocity){ curr.velocity.y = curr.maxVelocity; }
	}
	else
	{
		curr.acc.y *= aDecel;
		curr.velocity.y *= vDecel; //v += acc - friction*v
	}

	//move
	worldObjectManager.move(ID, sf::Vector2f(curr.velocity.x * deltaTime.asSeconds(), curr.velocity.y * deltaTime.asSeconds()));
	//world map then handles colisions - sends volume and location and origin - collision movement vector is returned
	sf::Vector2f collisionMovementVector = gameMap.checkForColision(graphicsManager.components.at(ID).sprite.getOrigin(), worldObjectManager.getLocationf(ID),
		worldObjectManager.sorter.find(ID)->dimentions, curr.velocity);
	worldObjectManager.move(ID, collisionMovementVector);

	//curr.velocity.x = 0;
	//curr.velocity.y = 0;
	curr.appliedForce = false;
	action.oldAngle = action.lookAngle;
}

void s_Physics::addComponent(unsigned int name, c_Physics newComponent){components.insert(std::pair<unsigned int, c_Physics>(name, newComponent));}

c_Physics& s_Physics::getComponent(unsigned int ID)
{
	std::map<unsigned int, c_Physics>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
	{
		if (it->first == ID){return it->second;}
	}
	try
	{throw;}
	catch (std::exception)//log issue occuring, try to handle if it happens
	{
		Locator::getConsole().log("SystemManager.findEntity() failed to find a valid ID value. " + std::to_string(ID) + " Not found.");
	}
	return c_Physics();
}

const std::map<unsigned int, c_Physics>& s_Physics::getComponentsMap(){return components;}

void s_Physics::removeComponent(unsigned int ID){components.erase(ID);}

void s_Physics::savetoFile(unsigned int ID, pugi::xml_node parent)
{
	pugi::xml_node curr = parent.append_child("physics");
	curr.append_child("maxvelocity");
	std::string temp = std::to_string(components[ID].maxVelocity);
	curr.child("maxvelocity").append_child(pugi::node_pcdata).set_value(temp.c_str());
}

s_Physics::~s_Physics(){}
