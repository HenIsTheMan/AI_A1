#pragma once

class StateOrcAttack final{ //Static class
	StateOrcAttack() = delete;
	~StateOrcAttack() = delete;
	StateOrcAttack(const StateOrcAttack&) = delete;
	StateOrcAttack(StateOrcAttack&&) noexcept = delete;
	StateOrcAttack& operator=(const StateOrcAttack&) = delete;
	StateOrcAttack& operator=(StateOrcAttack&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateOrcAttack.inl"