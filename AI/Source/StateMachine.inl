template <class T, typename Type>
StateMachine<T, Type>::StateMachine():
	im_States()
{
}

template <class T, typename Type>
void StateMachine<T, Type>::AddState(const T& stateID, State* const state){
	assert(state && "Var 'state' must be initialized!");

	im_States.emplace({stateID, state});
}

template <class T, typename Type>
const State* StateMachine<T, Type>::GetState(const T& stateID) const{
	assert(im_States.find(stateID) != im_States.end() && "stateID cannot be found!");

	return im_States.at(stateID);
}

template <class T, typename Type>
void StateMachine<T, Type>::Update(Type* const entity, const double dt){
	assert(entity->currState && "entity->currState must be initialized!");

	entity->currState->Update(dt);
}