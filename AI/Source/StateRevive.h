#pragma once

class StateRevive final{ //Static class
	StateRevive() = delete;
	~StateRevive() = delete;
	StateRevive(const StateRevive&) = delete;
	StateRevive(StateRevive&&) noexcept = delete;
	StateRevive& operator=(const StateRevive&) = delete;
	StateRevive& operator=(StateRevive&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateRevive.inl"