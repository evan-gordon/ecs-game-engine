//Evan Gordon

#ifndef CONVERSTIONS_H
#define CONVERSIONS_H

#include <cctype>
#include <string>
#include <cstdlib>

bool isInt(std::string string);
//write more as needed ----probably will need one for boolean

int toInt(std::string& string);//this function does not check for actual ints and only interprets the string given

#endif