#pragma once

class StateOrcImmune final{ //Static class
	StateOrcImmune() = delete;
	~StateOrcImmune() = delete;
	StateOrcImmune(const StateOrcImmune&) = delete;
	StateOrcImmune(StateOrcImmune&&) noexcept = delete;
	StateOrcImmune& operator=(const StateOrcImmune&) = delete;
	StateOrcImmune& operator=(StateOrcImmune&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateOrcImmune.inl"