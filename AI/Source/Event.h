#pragma once

#include "EventID.hpp"

///Better if templated

class Event{ //Abstract class
public:
	virtual ~Event() = default;

	///Getter
	EventID GetID() const;
protected:
	EventID im_ID;

	Event();
	Event(const EventID ID);
};