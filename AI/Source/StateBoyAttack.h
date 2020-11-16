#pragma once

class StateBoyAttack final{ //Static class
	StateBoyAttack() = delete;
	~StateBoyAttack() = delete;
	StateBoyAttack(const StateBoyAttack&) = delete;
	StateBoyAttack(StateBoyAttack&&) noexcept = delete;
	StateBoyAttack& operator=(const StateBoyAttack&) = delete;
	StateBoyAttack& operator=(StateBoyAttack&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateBoyAttack.inl"