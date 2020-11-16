#pragma once

class StateReptileDead final{ //Static class
	StateReptileDead() = delete;
	~StateReptileDead() = delete;
	StateReptileDead(const StateReptileDead&) = delete;
	StateReptileDead(StateReptileDead&&) noexcept = delete;
	StateReptileDead& operator=(const StateReptileDead&) = delete;
	StateReptileDead& operator=(StateReptileDead&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateReptileDead.inl"