#pragma once

#include <unordered_map>

template <class T, typename Type>
class StateMachine final{
public:
	StateMachine<T, Type>();
	~StateMachine<T, Type>() = default;

	void AddState(const T& stateID, State* const state);

	const State* GetState(const T& stateID) const;

	void Update(Type* const entity, const double dt);
private:
	std::unordered_map<T, State*> im_States;
};

#include "StateMachine.inl"