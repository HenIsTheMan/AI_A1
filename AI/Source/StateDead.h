#pragma once

class StateDead final{ //Static class
	StateDead() = delete;
	~StateDead() = delete;
	StateDead(const StateDead&) = delete;
	StateDead(StateDead&&) noexcept = delete;
	StateDead& operator=(const StateDead&) = delete;
	StateDead& operator=(StateDead&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateDead.inl"