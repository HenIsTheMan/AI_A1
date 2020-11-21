#pragma once

#include "Event.h"

#include "Entity.h"

class EventFindNearestObj final: public Event{
	EventFindNearestObj() = delete;
public:
	EventFindNearestObj(Obj::Entity<Vector3, float>* const entity);
	~EventFindNearestObj() = default;

	Obj::Entity<Vector3, float>* RetrieveEntity(); 
private:
	Obj::Entity<Vector3, float>* im_Entity;

	EventFindNearestObj* Clone() const override;
};