#pragma once

class StateSkeleIdle final{ //Static class
	StateSkeleIdle() = delete;
	~StateSkeleIdle() = delete;
	StateSkeleIdle(const StateSkeleIdle&) = delete;
	StateSkeleIdle(StateSkeleIdle&&) noexcept = delete;
	StateSkeleIdle& operator=(const StateSkeleIdle&) = delete;
	StateSkeleIdle& operator=(StateSkeleIdle&&) noexcept = delete;
public:
	static void Enter();
	static void Update(const double dt);
	static void Exit();
};

#include "StateSkeleIdle.inl"