#pragma once

#include "StateHelperFuncs.h"

class StateOrcCannotMove final{ //Static class
	StateOrcCannotMove() = delete;
	~StateOrcCannotMove() = delete;
	StateOrcCannotMove(const StateOrcCannotMove&) = delete;
	StateOrcCannotMove(StateOrcCannotMove&&) noexcept = delete;
	StateOrcCannotMove& operator=(const StateOrcCannotMove&) = delete;
	StateOrcCannotMove& operator=(StateOrcCannotMove&&) noexcept = delete;
public:
	static Grid<float>* im_Grid;
	static int im_GridRows;
	static int im_GridCols;

	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateOrcCannotMove.inl"