#pragma once

class StateImmune final{ //Static class
	StateImmune() = delete;
	~StateImmune() = delete;
	StateImmune(const StateImmune&) = delete;
	StateImmune(StateImmune&&) noexcept = delete;
	StateImmune& operator=(const StateImmune&) = delete;
	StateImmune& operator=(StateImmune&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateImmune.inl"