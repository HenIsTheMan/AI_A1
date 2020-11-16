#pragma once

class StateSkeleDead final{ //Static class
	StateSkeleDead() = delete;
	~StateSkeleDead() = delete;
	StateSkeleDead(const StateSkeleDead&) = delete;
	StateSkeleDead(StateSkeleDead&&) noexcept = delete;
	StateSkeleDead& operator=(const StateSkeleDead&) = delete;
	StateSkeleDead& operator=(StateSkeleDead&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateSkeleDead.inl"