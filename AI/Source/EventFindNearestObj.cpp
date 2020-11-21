#include "EventFindNearestObj.h"

EventFindNearestObj::EventFindNearestObj(Obj::Entity<Vector3, float>* const entity):
	Event(EventID::EventFindNearestObj),
	im_Entity(entity)
{
}

Obj::Entity<Vector3, float>* EventFindNearestObj::RetrieveEntity(){
	return im_Entity;
}

EventFindNearestObj* EventFindNearestObj::Clone() const{
	return new EventFindNearestObj(*this);
}