#pragma once

#include "Event.h"

class EventGridDataChanged final: public Event{
public:
	EventGridDataChanged();
	~EventGridDataChanged() = default;
};