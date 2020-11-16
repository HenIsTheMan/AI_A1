#pragma once

class StateOrcDead final{ //Static class
	StateOrcDead() = delete;
	~StateOrcDead() = delete;
	StateOrcDead(const StateOrcDead&) = delete;
	StateOrcDead(StateOrcDead&&) noexcept = delete;
	StateOrcDead& operator=(const StateOrcDead&) = delete;
	StateOrcDead& operator=(StateOrcDead&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateOrcDead.inl"