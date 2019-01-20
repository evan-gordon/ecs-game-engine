//Evan Gordon

#include "Files.h"

Files::Files()//load documents
{
	if (!console.load_file("xml/console/console.xml"))
	{
		throw 42;
	}
	if (!consoleReply.load_file("xml/console/consolereply.xml"))
	{
		throw 42;
	}
}

Files::~Files()
{
	console.save_file("../xml/console/console.xml");
	consoleReply.save_file("../xml/console/consolereply.xml");
}

pugi::xml_document Files::console;
pugi::xml_document Files::consoleReply;