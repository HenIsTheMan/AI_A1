#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

class StateReptileMultiply final{ //Static class
	StateReptileMultiply() = delete;
	~StateReptileMultiply() = delete;
	StateReptileMultiply(const StateReptileMultiply&) = delete;
	StateReptileMultiply(StateReptileMultiply&&) noexcept = delete;
	StateReptileMultiply& operator=(const StateReptileMultiply&) = delete;
	StateReptileMultiply& operator=(StateReptileMultiply&&) noexcept = delete;
public:
	static void Enter(Entity* const entity);
	static void Update(Entity* const entity, const double dt);
	static void Exit(Entity* const entity);
};

#include "StateReptileMultiply.inl"