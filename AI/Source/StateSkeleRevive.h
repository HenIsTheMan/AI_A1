#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateSkeleRevive final{ //Static class
	StateSkeleRevive() = delete;
	~StateSkeleRevive() = delete;
	StateSkeleRevive(const StateSkeleRevive&) = delete;
	StateSkeleRevive(StateSkeleRevive&&) noexcept = delete;
	StateSkeleRevive& operator=(const StateSkeleRevive&) = delete;
	StateSkeleRevive& operator=(StateSkeleRevive&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleRevive.inl"