#pragma once

#include "StateHelperFuncs.h"

class StateReptileCannotMove final{ //Static class
	StateReptileCannotMove() = delete;
	~StateReptileCannotMove() = delete;
	StateReptileCannotMove(const StateReptileCannotMove&) = delete;
	StateReptileCannotMove(StateReptileCannotMove&&) noexcept = delete;
	StateReptileCannotMove& operator=(const StateReptileCannotMove&) = delete;
	StateReptileCannotMove& operator=(StateReptileCannotMove&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateReptileCannotMove.inl"