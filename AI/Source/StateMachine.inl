template <class T, typename Type>
StateMachine<T, Type>::StateMachine():
	im_States()
{
}

template <class T, typename Type>
void StateMachine<T, Type>::AddState(const T& stateID, State* const state){
	#if defined _DEBUG
	assert(state && "Var 'state' must be initialized!");
	#endif

	im_States.emplace({stateID, state});
}

template <class T, typename Type>
const State* StateMachine<T, Type>::GetState(const T& stateID) const{
	#if defined _DEBUG
	assert(im_States.find(stateID) != im_States.end() && "stateID cannot be found!");
	#endif

	return im_States.at(stateID);
}

template <class T, typename Type>
void StateMachine<T, Type>::Update(Type* const entity, const double dt){
	#if defined _DEBUG
	assert(entity->currState && "entity->currState must be initialized!");
	#endif

	entity->currState->Update(dt);
}