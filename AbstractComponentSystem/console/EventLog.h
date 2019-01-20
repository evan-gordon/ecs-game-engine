//Evan Gordon

#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <string>
#include <vector>
#include <deque>


/*This class is for logging the last 50 events in the game. It also keeps track of the last time it's events list was read with newEvents
	newEvents is to be reset every time the list is read.*/
class EventLog
{
public:
	EventLog();

	void push(const std::string&);
	void pop();
	std::vector<std::string> read();

	~EventLog();

private:
	short int newEvents;
	std::deque<std::string> log;
};

#endif