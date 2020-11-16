#pragma once

class StateBoyDead final{ //Static class
	StateBoyDead() = delete;
	~StateBoyDead() = delete;
	StateBoyDead(const StateBoyDead&) = delete;
	StateBoyDead(StateBoyDead&&) noexcept = delete;
	StateBoyDead& operator=(const StateBoyDead&) = delete;
	StateBoyDead& operator=(StateBoyDead&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateBoyDead.inl"