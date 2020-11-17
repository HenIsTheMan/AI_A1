#pragma once

#include "EntityHelperFuncs.h"

class StateReptileIdle final{ //Static class
	StateReptileIdle() = delete;
	~StateReptileIdle() = delete;
	StateReptileIdle(const StateReptileIdle&) = delete;
	StateReptileIdle(StateReptileIdle&&) noexcept = delete;
	StateReptileIdle& operator=(const StateReptileIdle&) = delete;
	StateReptileIdle& operator=(StateReptileIdle&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateReptileIdle.inl"