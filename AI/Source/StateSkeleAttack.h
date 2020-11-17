#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateSkeleAttack final{ //Static class
	StateSkeleAttack() = delete;
	~StateSkeleAttack() = delete;
	StateSkeleAttack(const StateSkeleAttack&) = delete;
	StateSkeleAttack(StateSkeleAttack&&) noexcept = delete;
	StateSkeleAttack& operator=(const StateSkeleAttack&) = delete;
	StateSkeleAttack& operator=(StateSkeleAttack&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleAttack.inl"