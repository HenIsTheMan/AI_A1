#include "EventFindNearestObj.h"

EventFindNearestObj::EventFindNearestObj():
	Event(EventID::EventFindNearestObj)
{
}

EventFindNearestObj* EventFindNearestObj::Clone() const{
	return new EventFindNearestObj(*this);
}