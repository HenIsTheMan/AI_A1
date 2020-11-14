#include "EventApproaching.h"

EventApproaching::EventApproaching():
	EventApproaching(nullptr)
{
}

EventApproaching::EventApproaching(Obj::Entity<Vector3, float>* const entity):
	IEvent(),
	im_Entity(entity)
{
}

const Obj::Entity<Vector3, float>* EventApproaching::GetEntity() const{
	return im_Entity;
}