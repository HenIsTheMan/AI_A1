#pragma once

#include "StateHelperFuncs.h"

class StateBoyCannotMove final{ //Static class
	StateBoyCannotMove() = delete;
	~StateBoyCannotMove() = delete;
	StateBoyCannotMove(const StateBoyCannotMove&) = delete;
	StateBoyCannotMove(StateBoyCannotMove&&) noexcept = delete;
	StateBoyCannotMove& operator=(const StateBoyCannotMove&) = delete;
	StateBoyCannotMove& operator=(StateBoyCannotMove&&) noexcept = delete;
public:
	static float im_ElapsedTime;
	static Grid<float>* im_Grid;
	static int im_GridRows;
	static int im_GridCols;

	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateBoyCannotMove.inl"