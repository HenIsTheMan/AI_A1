#pragma once

#include "EventID.hpp"

class Event{
public:
	virtual ~Event() = default;
protected:
	EventID im_ID;

	Event();
	Event(const EventID ID);
};