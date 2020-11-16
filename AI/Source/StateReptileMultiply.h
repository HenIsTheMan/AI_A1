#pragma once

class StateReptileMultiply final{ //Static class
	StateReptileMultiply() = delete;
	~StateReptileMultiply() = delete;
	StateReptileMultiply(const StateReptileMultiply&) = delete;
	StateReptileMultiply(StateReptileMultiply&&) noexcept = delete;
	StateReptileMultiply& operator=(const StateReptileMultiply&) = delete;
	StateReptileMultiply& operator=(StateReptileMultiply&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateReptileMultiply.inl"