#pragma once

#include <unordered_map>

template <class T, typename Type>
class StateMachine final{
public:
	StateMachine<T, Type>();
	~StateMachine<T, Type>() = default;

	void AddState(const T& stateID, State* const state);
	void ChangeCurrState(Type* const entity);
	void UpdateCurrState(Type* const entity, const double dt);

	///Getter
	const State* GetState(const T& stateID) const;
private:
	std::unordered_map<T, State*> im_States;
};

#include "StateMachine.inl"