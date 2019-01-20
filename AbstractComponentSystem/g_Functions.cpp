//Evan Gordon

//Global Functions, User discrescion is advised
//consider moving some of this code to the service provider?

#include "g_Functions.h"
unsigned int lowestSerial = 1;
float sinArr[deg],  cosArr[deg];

void resetSerial()
{
	lowestSerial = 1;
}

unsigned int serialize()
{
	if(lowestSerial < UINT_MAX)
	{
		unsigned int result = lowestSerial;
		lowestSerial++;
		return result;
	}
	else
	{
		for(int i = 0; i < UINT_MAX; i++)
		{
			//if that id doesnt exist return it
		}
	}
	try
	{
		throw;
	}
	catch(std::exception)//log issue occuring, try to handle if it happens
	{
		return 0;//0 is invalid value
	}
	return 0;//0 is invalid value
}

std::vector<unsigned int> serializeMultiple(int numToSerialize)
{
	std::vector<unsigned int> t;
	for(int i = 0; i < numToSerialize; i++)
	{t.push_back(serialize());}
	return t;
}

float randBetween(float lower, float upper)
{
	float diff = upper - lower;
	return (((float)rand() / RAND_MAX) * diff) + lower;
}

sf::Keyboard::Key stringToKeyboardKey(std::string key)
{
	if(key == "a")
	{return sf::Keyboard::Key::A;}
	else if(key == "b")
	{return sf::Keyboard::Key::B;}
	else if(key == "c")
	{return sf::Keyboard::Key::C;}
	else if(key == "d")
	{return sf::Keyboard::Key::D;}
	else if(key == "e")
	{return sf::Keyboard::Key::E;}
	else if(key == "f")
	{return sf::Keyboard::Key::F;}
	else if(key == "g")
	{return sf::Keyboard::Key::G;}
	else if(key == "h")
	{return sf::Keyboard::Key::H;}
	else if(key == "i")
	{return sf::Keyboard::Key::I;}
	else if(key == "j")
	{return sf::Keyboard::Key::J;}
	else if(key == "k")
	{return sf::Keyboard::Key::K;}
	else if(key == "l")
	{return sf::Keyboard::Key::L;}
	else if(key == "m")
	{return sf::Keyboard::Key::M;}
	else if(key == "n")
	{return sf::Keyboard::Key::N;}
	else if(key == "o")
	{return sf::Keyboard::Key::O;}
	else if(key == "p")
	{return sf::Keyboard::Key::P;}
	else if(key == "q")
	{return sf::Keyboard::Key::Q;}
	else if(key == "r")
	{return sf::Keyboard::Key::R;}
	else if(key == "s")
	{return sf::Keyboard::Key::S;}
	else if(key == "t")
	{return sf::Keyboard::Key::T;}
	else if(key == "u")
	{return sf::Keyboard::Key::U;}
	else if(key == "v")
	{return sf::Keyboard::Key::V;}
	else if(key == "w")
	{return sf::Keyboard::Key::W;}
	else if(key == "x")
	{return sf::Keyboard::Key::X;}
	else if(key == "y")
	{return sf::Keyboard::Key::Y;}
	else if(key == "z")
	{return sf::Keyboard::Key::Z;}
	else if(key == "space")
	{return sf::Keyboard::Key::Space;}
	else if(key == "tab")
	{return sf::Keyboard::Key::Tab;}
	else if(key == "left")
	{return sf::Keyboard::Key::Left;}
	else if(key == "up")
	{return sf::Keyboard::Key::Up;}
	else if(key == "down")
	{return sf::Keyboard::Key::Down;}
	else if(key == "right")
	{return sf::Keyboard::Key::Right;}
	else if(key == "leftshift")
	{return sf::Keyboard::LShift;}
	else if(key == "leftcontrol")
	{return sf::Keyboard::LControl;}
	else if(key == "leftalt")
	{return sf::Keyboard::LAlt;}
	else if(key == "backspace")
	{return sf::Keyboard::BackSpace;}
	else if(key == "rightalt")
	{return sf::Keyboard::RAlt;}
	else if(key == "rightshift")
	{return sf::Keyboard::RShift;}
	else if(key == "rightcontrol")
	{return sf::Keyboard::RControl;}
	else if(key == "home")
	{return sf::Keyboard::Home;}
	else if(key == "pgup")
	{return sf::Keyboard::PageUp;}
	else if(key == "pgdn")
	{return sf::Keyboard::PageDown;}
	else if(key == "delete")
	{return sf::Keyboard::Delete;}
	else if(key == "insert")
	{return sf::Keyboard::Insert;}
	else if(key == "end")
	{return sf::Keyboard::End;}
	else if(key == "num0")
	{return sf::Keyboard::Num0;}
	else if(key == "num1")
	{return sf::Keyboard::Num1;}
	else if(key == "num2")
	{return sf::Keyboard::Num2;}
	else if(key == "num3")
	{return sf::Keyboard::Num3;}
	else if(key == "num4")
	{return sf::Keyboard::Num4;}
	else if(key == "num5")
	{return sf::Keyboard::Num5;}
	else if(key == "num6")
	{return sf::Keyboard::Num6;}
	else if(key == "num7")
	{return sf::Keyboard::Num7;}
	else if(key == "num8")
	{return sf::Keyboard::Num8;}
	else if(key == "num9")
	{return sf::Keyboard::Num9;}
	else
	{
		std::cout<<"Error with key assignment for key: "<< key<<"\n";
		throw(42);
	}
}

sf::Mouse::Button stringToMouseButton(std::string key)
{
	if(key == "left")
	{return sf::Mouse::Button::Left;}
	else if(key == "right")
	{
		return sf::Mouse::Button::Right;
	}//nothing else should be happening
	else
	{
		std::cout<<"Error with key assignment for key: "<< key<<"\n";
		throw(42);
	}
}

int numberOfNodes(pugi::xml_node node)
{
	int i = 0; 
	for(auto curr = node.first_child(); curr; curr = curr.next_sibling())
	{
		i++;
	}
	return i;
}

void initTrig()
{
	for(int i = 0; i < deg; i++)
	{
		sinArr[i] = std::sin((i * PI) / 180.0f);
		cosArr[i] = std::cos((i * PI) / 180.0f);		
	}
}

Direction vectorToDirection(sf::Vector2i v)
{
	if (v.x > 0)
	{
		if (v.y < 0)
		{
			return UPRIGHT;
		}
		else if (v.y > 0)
		{
			return DOWNRIGHT;
		}
		else
		{
			return RIGHT;
		}
	}
	else if (v.x < 0)
	{
		if (v.y < 0)
		{
			return UPLEFT;
		}
		else if (v.y > 0)
		{
			return DOWNLEFT;
		}
		else
		{
			return LEFT;
		}
	}
	else
	{
		if (v.y < 0)
		{
			return UP;
		}
		else if (v.y > 0)
		{
			return DOWN;
		}
		else
		{
			return Direction::NONE;
		}
	}
}

int angleBetween(sf::Vector2f origin, sf::Vector2f dest){ return (std::atan2((dest.y - origin.y), (dest.x - origin.x)) * 180.0) / PI + .5; }

float calcVectorX(float magnitude, int direction){return magnitude * cosArr[direction];}

float calcVectorY(float magnitude, int direction){return magnitude * sinArr[direction];}

//check for collision, return true if overlapping
bool checkCollision(const sf::Vector2f& center1, const sf::Vector2f& halfW1, const sf::Vector2f& center2, const sf::Vector2f& halfW2)
{
	if (center1.x - halfW1.x >= center2.x + halfW2.x || center1.x + halfW1.x <= center2.x - halfW2.x ||
		center1.y - halfW1.y >= center2.y + halfW2.y || center1.y + halfW1.y <= center2.y - halfW2.y)//no collision
	{return false;}

	return true;
}

//Returns movement vector for nonstatic object, arguments are box1 center, halfdimentions, and the same for box2
sf::Vector2f boxToStaticBoxCollision(sf::Vector2f center1, sf::Vector2f halfW1, sf::Vector2f& velocity, sf::Vector2f center2, sf::Vector2f halfW2)
{
	sf::Vector2f movementVector(0, 0);//used for result
	if(center1.x - halfW1.x >= center2.x + halfW2.x || center1.x + halfW1.x <= center2.x - halfW2.x ||
			center1.y - halfW1.y >= center2.y + halfW2.y || center1.y + halfW1.y <= center2.y - halfW2.y)//no collision
	{return movementVector;}

	//rule out super fast motion involved in clipping for now
	if(velocity.x < 0 && center1.x - halfW1.x < center2.x + halfW2.x && center1.x - halfW1.x > center2.x)
	{
		movementVector.x = (center2.x + halfW2.x) - (center1.x - halfW1.x);//push right
	}
	else if(velocity.x > 0 && center1.x + halfW1.x > center2.x - halfW2.x && center1.x + halfW1.x < center2.x)
	{
		movementVector.x = -((center1.x + halfW1.x) - (center2.x - halfW2.x));//push left
	}
	else if(velocity.y < 0 && center1.y - halfW1.y < center2.y + halfW2.y && center1.y - halfW1.y > center2.y)
	{
		movementVector.y = (center2.y + halfW2.y) - (center1.y - halfW1.y);//push down
	}
	else if(velocity.y > 0 && center1.y + halfW1.y > center2.y - halfW2.y && center1.y + halfW1.y < center2.y)
	{
		movementVector.y = -((center1.y + halfW1.y) - (center2.y - halfW2.y));//push up
	}
	return movementVector;
}