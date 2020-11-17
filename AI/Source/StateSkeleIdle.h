#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateSkeleIdle final{ //Static class
	StateSkeleIdle() = delete;
	~StateSkeleIdle() = delete;
	StateSkeleIdle(const StateSkeleIdle&) = delete;
	StateSkeleIdle(StateSkeleIdle&&) noexcept = delete;
	StateSkeleIdle& operator=(const StateSkeleIdle&) = delete;
	StateSkeleIdle& operator=(StateSkeleIdle&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleIdle.inl"