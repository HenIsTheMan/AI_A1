#pragma once

class StateHeal final{ //Static class
	StateHeal() = delete;
	~StateHeal() = delete;
	StateHeal(const StateHeal&) = delete;
	StateHeal(StateHeal&&) noexcept = delete;
	StateHeal& operator=(const StateHeal&) = delete;
	StateHeal& operator=(StateHeal&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateHeal.inl"