//Evan Gordon

#ifndef FILES_H
#define FILES_H

#include "../pugixml.hpp"

#include <exception>

//A simple container class for the xml files the console will need
//the reply and console files are split up so as to maintain unability between this and other projects
class Files
{
public:
	static pugi::xml_document console;
	static pugi::xml_document consoleReply;

	Files();//load documents
	~Files();
};

#endif