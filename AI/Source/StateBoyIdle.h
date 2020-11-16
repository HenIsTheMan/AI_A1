#pragma once

class StateBoyIdle final{ //Static class
	StateBoyIdle() = delete;
	~StateBoyIdle() = delete;
	StateBoyIdle(const StateBoyIdle&) = delete;
	StateBoyIdle(StateBoyIdle&&) noexcept = delete;
	StateBoyIdle& operator=(const StateBoyIdle&) = delete;
	StateBoyIdle& operator=(StateBoyIdle&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateBoyIdle.inl"