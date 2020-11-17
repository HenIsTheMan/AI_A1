#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateOrcDead final{ //Static class
	StateOrcDead() = delete;
	~StateOrcDead() = delete;
	StateOrcDead(const StateOrcDead&) = delete;
	StateOrcDead(StateOrcDead&&) noexcept = delete;
	StateOrcDead& operator=(const StateOrcDead&) = delete;
	StateOrcDead& operator=(StateOrcDead&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateOrcDead.inl"