#pragma once

#include "EntityHelperFuncs.h"

class StateBoyIdle final{ //Static class
	StateBoyIdle() = delete;
	~StateBoyIdle() = delete;
	StateBoyIdle(const StateBoyIdle&) = delete;
	StateBoyIdle(StateBoyIdle&&) noexcept = delete;
	StateBoyIdle& operator=(const StateBoyIdle&) = delete;
	StateBoyIdle& operator=(StateBoyIdle&&) noexcept = delete;
public:
	static Grid<float>* im_Grid;
	static int im_GridRows;
	static int im_GridCols;

	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateBoyIdle.inl"