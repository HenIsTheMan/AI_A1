#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateBoyIdle final{ //Static class
	StateBoyIdle() = delete;
	~StateBoyIdle() = delete;
	StateBoyIdle(const StateBoyIdle&) = delete;
	StateBoyIdle(StateBoyIdle&&) noexcept = delete;
	StateBoyIdle& operator=(const StateBoyIdle&) = delete;
	StateBoyIdle& operator=(StateBoyIdle&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateBoyIdle.inl"