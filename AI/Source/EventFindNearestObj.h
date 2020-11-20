#pragma once

#include "Event.h"

class EventFindNearestObj final: public Event{
public:
	EventFindNearestObj();
	~EventFindNearestObj() = default;
private:
	EventFindNearestObj* Clone() const override;
};