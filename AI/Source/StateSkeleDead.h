#pragma once

#include "EntityHelperFuncs.h"

class StateSkeleDead final{ //Static class
	StateSkeleDead() = delete;
	~StateSkeleDead() = delete;
	StateSkeleDead(const StateSkeleDead&) = delete;
	StateSkeleDead(StateSkeleDead&&) noexcept = delete;
	StateSkeleDead& operator=(const StateSkeleDead&) = delete;
	StateSkeleDead& operator=(StateSkeleDead&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateSkeleDead.inl"