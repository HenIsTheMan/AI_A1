#include "StateMachine.h"

StateMachine::StateMachine():
	im_stateMap()
{
}

StateMachine::~StateMachine()
{
	for (std::map<std::string, State*>::iterator it = im_stateMap.begin(); it != im_stateMap.end(); ++it)
	{
		delete it->second;
	}
	im_stateMap.clear();
}

void StateMachine::AddState(State* const& newState)
{
	if (!newState)
		return;
	if (im_stateMap.find(newState->GetStateID()) != im_stateMap.end())
		return;
	im_stateMap.insert(std::pair<std::string, State*>(newState->GetStateID(), newState));
}

State* const& StateMachine::GetState(const std::string& stateID) const{
	return im_stateMap.at(stateID);
}

void StateMachine::Update(GameObject *go, double dt)
{
	go->currState->Update(go, dt);
}
