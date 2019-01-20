//Evan Gordon

#include "EventLog.h"

EventLog::EventLog():
	newEvents(0)
{}

//pushes given string event onto log stack to be read. /n is automatically applied
void EventLog::push(const std::string& event)
{
	if(event.size() == 0){return;}

	log.push_front(event);
	newEvents++;
	if(log.size() > 50){pop();}
}

void EventLog::pop()
{
	log.pop_back();
	if(newEvents > (int)log.size()){newEvents--;}
}

std::vector<std::string> EventLog::read()
{
	std::vector<std::string> result;
	for(int i = (newEvents - 1); i >= 0; i--)
	{
		result.push_back(log[i] + "\n");
	}
	newEvents = 0;
	return result;
}

EventLog::~EventLog(){}