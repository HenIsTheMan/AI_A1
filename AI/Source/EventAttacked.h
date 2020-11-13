#pragma once

#include "IEvent.hpp"

#include "Entity.h"

class EventAttacked final: public IEvent{
public:
	EventAttacked();
	EventAttacked(Obj::Entity<Vector3, float>* const entity);
	~EventAttacked() = default;

	///Getter
	const Obj::Entity<Vector3, float>* GetEntity() const; 
private:
	Obj::Entity<Vector3, float>* im_Entity;
};