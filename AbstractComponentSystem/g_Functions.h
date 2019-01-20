//Evan Gordon

#ifndef G_FUNCTIONS_H
#define G_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "pugixml.hpp"

#include "systems/components/c_Action.h"

#include <math.h>
#include <cmath>
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <limits.h>
#include <stdint.h>
#include <memory>

#define PI 3.14159265
#define deg 360

//might have to use none, for when state isnt changed, pop is used to exit curr state
enum StateType{ Main, CreateMap, CreateSave, Edit, Play, SelectMap, SelectSave, Settings, None, Pop };//add one more later for slecting save files
enum Trig{Sin, Cos};

extern unsigned int lowestSerial;
extern float sinArr[deg], cosArray[deg];

void resetSerial();
unsigned int serialize();
float randBetween(float lower, float upper);
std::vector<unsigned int> serializeMultiple(int numToSerialize);

sf::Keyboard::Key stringToKeyboardKey(std::string key);
sf::Mouse::Button stringToMouseButton(std::string key);

int numberOfNodes(pugi::xml_node node);

void initTrig();

Direction vectorToDirection(sf::Vector2i vector);

int angleBetween(sf::Vector2f origin, sf::Vector2f dest);
float calcVectorX(float magnitude, int direction);
float calcVectorY(float magnitude, int direction);

bool checkCollision(const sf::Vector2f& center1, const sf::Vector2f& halfW1, const sf::Vector2f& center2, const sf::Vector2f& halfW2);
sf::Vector2f boxToStaticBoxCollision(sf::Vector2f center1, sf::Vector2f halfW1, sf::Vector2f& velocity, sf::Vector2f center2, sf::Vector2f halfW2);

namespace util//borrowed from: http://www.cplusplus.com/forum/beginner/154004/
{
    #if __cplusplus == 201402L // C++14

        using std::make_unique ;

    #else // C++11

        template < typename T, typename... CONSTRUCTOR_ARGS >
        std::unique_ptr<T> make_unique( CONSTRUCTOR_ARGS&&... constructor_args )
        { return std::unique_ptr<T>( new T( std::forward<CONSTRUCTOR_ARGS>(constructor_args)... ) ); }

    #endif // __cplusplus == 201402L
}
#endif