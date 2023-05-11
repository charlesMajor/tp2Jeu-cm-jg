#pragma once
#include <map>
#include "event.h"

struct Subscriber;

class Publisher
{
public:
	static void addSubscriber(Subscriber& o, Event event);
	static void removeSubscriber(Subscriber& o, Event event);
	static void notifySubscribers(Event event, const void* data);

private:
	Publisher();
	Publisher(const Publisher&);
	Publisher& operator=(const Publisher&);
	static std::multimap<Event, std::reference_wrapper<Subscriber> > subscribers;
};