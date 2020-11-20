#pragma once

#include "StateHelperFuncs.h"

class StateBoyHeal final{ //Static class
	StateBoyHeal() = delete;
	~StateBoyHeal() = delete;
	StateBoyHeal(const StateBoyHeal&) = delete;
	StateBoyHeal(StateBoyHeal&&) noexcept = delete;
	StateBoyHeal& operator=(const StateBoyHeal&) = delete;
	StateBoyHeal& operator=(StateBoyHeal&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateBoyHeal.inl"