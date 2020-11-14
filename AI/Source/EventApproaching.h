#pragma once

#include "IEvent.hpp"

#include "Entity.h"

class EventApproaching final: public IEvent{
public:
	EventApproaching();
	EventApproaching(Obj::Entity<Vector3, float>* const entity);
	~EventApproaching() = default;

	///Getter
	const Obj::Entity<Vector3, float>* GetEntity() const; 
private:
	Obj::Entity<Vector3, float>* im_Entity;
};