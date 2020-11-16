#pragma once

class StateReptileIdle final{ //Static class
	StateReptileIdle() = delete;
	~StateReptileIdle() = delete;
	StateReptileIdle(const StateReptileIdle&) = delete;
	StateReptileIdle(StateReptileIdle&&) noexcept = delete;
	StateReptileIdle& operator=(const StateReptileIdle&) = delete;
	StateReptileIdle& operator=(StateReptileIdle&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateReptileIdle.inl"