#pragma once

#include "EntityHelperFuncs.h"

class StateSkeleIdle final{ //Static class
	StateSkeleIdle() = delete;
	~StateSkeleIdle() = delete;
	StateSkeleIdle(const StateSkeleIdle&) = delete;
	StateSkeleIdle(StateSkeleIdle&&) noexcept = delete;
	StateSkeleIdle& operator=(const StateSkeleIdle&) = delete;
	StateSkeleIdle& operator=(StateSkeleIdle&&) noexcept = delete;
public:
	static Grid<float>* im_Grid;
	static int im_GridRows;
	static int im_GridCols;

	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleIdle.inl"