#include "EventFindNearestObj.h"

EventFindNearestObj::EventFindNearestObj(const EntityTeam team):
	Event(EventID::EventFindNearestObj),
	im_Team(team)
{
}

EntityTeam EventFindNearestObj::GetTeam() const{
	return im_Team;
}

EventFindNearestObj* EventFindNearestObj::Clone() const{
	return new EventFindNearestObj(*this);
}