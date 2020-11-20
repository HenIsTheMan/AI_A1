#pragma once

#include "StateHelperFuncs.h"

class StateSkeleCannotMove final{ //Static class
	StateSkeleCannotMove() = delete;
	~StateSkeleCannotMove() = delete;
	StateSkeleCannotMove(const StateSkeleCannotMove&) = delete;
	StateSkeleCannotMove(StateSkeleCannotMove&&) noexcept = delete;
	StateSkeleCannotMove& operator=(const StateSkeleCannotMove&) = delete;
	StateSkeleCannotMove& operator=(StateSkeleCannotMove&&) noexcept = delete;
public:
	static float im_ElapsedTime;
	static Grid<float>* im_Grid;

	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleCannotMove.inl"