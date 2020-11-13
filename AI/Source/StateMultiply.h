#pragma once

class StateMultiply final{ //Static class
	StateMultiply() = delete;
	~StateMultiply() = delete;
	StateMultiply(const StateMultiply&) = delete;
	StateMultiply(StateMultiply&&) noexcept = delete;
	StateMultiply& operator=(const StateMultiply&) = delete;
	StateMultiply& operator=(StateMultiply&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateMultiply.inl"