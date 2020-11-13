#pragma once

#include <queue>

#include "IEvent.hpp"

class Listener{ //Abstract class
public:
	virtual int OnEvent(const IEvent* const myEvent, const bool destroyEvent = false) = 0;

	void AddEvent(IEvent* const myEvent);
	const IEvent* FetchEvent();
protected:
	std::queue<IEvent*> events;

	Listener();
	virtual ~Listener();
};