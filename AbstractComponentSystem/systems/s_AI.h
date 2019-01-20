//Alexander Frisk

#ifndef S_AI_H
#define S_AI_H

#include <random>
#include <fstream>

#include "../pugixml.hpp"

#include "components\c_AI.h"
#include "s_Action.h"

class s_AI :public Component
{
public:
	s_AI(s_Action& actionManager);
	~s_AI();

	s_Action& actionManager;

	void update(int deltaTime);
	void saveToFile(const unsigned int& ID, pugi::xml_node& parent);
	void addComponent(unsigned int ID, std::string type);
	void removeComponent(const unsigned int& ID);
	void updateMovement(unsigned int ID, std::string type);

	std::map<unsigned int, c_AI> components;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)

	std::ofstream log;
};

#endif