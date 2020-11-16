#pragma once

class StateOrcIdle final{ //Static class
	StateOrcIdle() = delete;
	~StateOrcIdle() = delete;
	StateOrcIdle(const StateOrcIdle&) = delete;
	StateOrcIdle(StateOrcIdle&&) noexcept = delete;
	StateOrcIdle& operator=(const StateOrcIdle&) = delete;
	StateOrcIdle& operator=(StateOrcIdle&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateOrcIdle.inl"