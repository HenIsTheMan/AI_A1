#pragma once

#include "EntityHelperFuncs.h"

class StateBoyAttack final{ //Static class
	StateBoyAttack() = delete;
	~StateBoyAttack() = delete;
	StateBoyAttack(const StateBoyAttack&) = delete;
	StateBoyAttack(StateBoyAttack&&) noexcept = delete;
	StateBoyAttack& operator=(const StateBoyAttack&) = delete;
	StateBoyAttack& operator=(StateBoyAttack&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateBoyAttack.inl"