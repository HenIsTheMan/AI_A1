#pragma once

class StateAttack final{ //Static class
	StateAttack() = delete;
	~StateAttack() = delete;
	StateAttack(const StateAttack&) = delete;
	StateAttack(StateAttack&&) noexcept = delete;
	StateAttack& operator=(const StateAttack&) = delete;
	StateAttack& operator=(StateAttack&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateAttack.inl"