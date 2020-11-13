#pragma once

class StateIdle final{ //Static class
	StateIdle() = delete;
	~StateIdle() = delete;
	StateIdle(const StateIdle&) = delete;
	StateIdle(StateIdle&&) noexcept = delete;
	StateIdle& operator=(const StateIdle&) = delete;
	StateIdle& operator=(StateIdle&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateIdle.inl"