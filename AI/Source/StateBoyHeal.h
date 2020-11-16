#pragma once

class StateBoyHeal final{ //Static class
	StateBoyHeal() = delete;
	~StateBoyHeal() = delete;
	StateBoyHeal(const StateBoyHeal&) = delete;
	StateBoyHeal(StateBoyHeal&&) noexcept = delete;
	StateBoyHeal& operator=(const StateBoyHeal&) = delete;
	StateBoyHeal& operator=(StateBoyHeal&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateBoyHeal.inl"