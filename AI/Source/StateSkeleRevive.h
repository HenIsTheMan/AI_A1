#pragma once

class StateSkeleRevive final{ //Static class
	StateSkeleRevive() = delete;
	~StateSkeleRevive() = delete;
	StateSkeleRevive(const StateSkeleRevive&) = delete;
	StateSkeleRevive(StateSkeleRevive&&) noexcept = delete;
	StateSkeleRevive& operator=(const StateSkeleRevive&) = delete;
	StateSkeleRevive& operator=(StateSkeleRevive&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateSkeleRevive.inl"