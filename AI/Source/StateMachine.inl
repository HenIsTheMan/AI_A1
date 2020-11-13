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
void StateMachine<T, Type>::ChangeCurrState(Type* const entity){
	assert(entity && "entity must be initialized!");
	assert(entity->im_NextState && "entity->im_NextState must be initialized!");

	if(entity->im_CurrState != entity->im_NextState){
		if(entity->im_CurrState){
			entity->im_CurrState->Exit();
			entity->im_CurrState = entity->im_NextState;
			entity->im_CurrState->Enter();
		} else{
			entity->im_CurrState = entity->im_NextState;
		}
	}
}

template <class T, typename Type>
void StateMachine<T, Type>::UpdateCurrState(Type* const entity, const double dt){
	assert(entity && "entity must be initialized!");
	assert(entity->im_CurrState && "entity->im_CurrState must be initialized!");

	entity->im_CurrState->Update(dt);
}

template <class T, typename Type>
const State* StateMachine<T, Type>::GetState(const T& stateID) const{
	assert(im_States.find(stateID) != im_States.end() && "stateID cannot be found!");

	return im_States.at(stateID);
}