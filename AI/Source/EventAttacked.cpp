#include "EventAttacked.h"

EventAttacked::EventAttacked():
	EventAttacked(nullptr)
{
}

EventAttacked::EventAttacked(Obj::Entity<Vector3, float>* const entity):
	im_Entity(entity)
{
}

const Obj::Entity<Vector3, float>* EventAttacked::GetEntity() const{
	return im_Entity;
}