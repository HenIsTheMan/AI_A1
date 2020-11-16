#pragma once

class StateSkeleAttack final{ //Static class
	StateSkeleAttack() = delete;
	~StateSkeleAttack() = delete;
	StateSkeleAttack(const StateSkeleAttack&) = delete;
	StateSkeleAttack(StateSkeleAttack&&) noexcept = delete;
	StateSkeleAttack& operator=(const StateSkeleAttack&) = delete;
	StateSkeleAttack& operator=(StateSkeleAttack&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateSkeleAttack.inl"