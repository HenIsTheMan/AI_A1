#pragma once

class StateReptileAttack final{ //Static class
	StateReptileAttack() = delete;
	~StateReptileAttack() = delete;
	StateReptileAttack(const StateReptileAttack&) = delete;
	StateReptileAttack(StateReptileAttack&&) noexcept = delete;
	StateReptileAttack& operator=(const StateReptileAttack&) = delete;
	StateReptileAttack& operator=(StateReptileAttack&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateReptileAttack.inl"