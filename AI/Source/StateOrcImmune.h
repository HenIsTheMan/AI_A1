#pragma once

#include "EntityHelperFuncs.h"

class StateOrcImmune final{ //Static class
	StateOrcImmune() = delete;
	~StateOrcImmune() = delete;
	StateOrcImmune(const StateOrcImmune&) = delete;
	StateOrcImmune(StateOrcImmune&&) noexcept = delete;
	StateOrcImmune& operator=(const StateOrcImmune&) = delete;
	StateOrcImmune& operator=(StateOrcImmune&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateOrcImmune.inl"