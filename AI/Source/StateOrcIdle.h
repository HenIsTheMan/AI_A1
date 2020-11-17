#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateOrcIdle final{ //Static class
	StateOrcIdle() = delete;
	~StateOrcIdle() = delete;
	StateOrcIdle(const StateOrcIdle&) = delete;
	StateOrcIdle(StateOrcIdle&&) noexcept = delete;
	StateOrcIdle& operator=(const StateOrcIdle&) = delete;
	StateOrcIdle& operator=(StateOrcIdle&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateOrcIdle.inl"