//#include "StateMachine.h"
//
//StateMachine::StateMachine():
//	m_stateMap()
//{
//}
//
//StateMachine::~StateMachine()
//{
//	for (std::map<std::string, State*>::iterator it = m_stateMap.begin(); it != m_stateMap.end(); ++it)
//	{
//		delete it->second;
//	}
//	m_stateMap.clear();
//}
//
//void StateMachine::AddState(State* const& newState)
//{
//	if (!newState)
//		return;
//	if (m_stateMap.find(newState->GetStateID()) != m_stateMap.end())
//		return;
//	m_stateMap.insert(std::pair<std::string, State*>(newState->GetStateID(), newState));
//}
//
//State* const& StateMachine::GetState(const std::string& stateID) const{
//	return m_stateMap.at(stateID);
//}
//
//void StateMachine::Update(GameObject *go, double dt)
//{
//	go->currState->Update(go, dt);
//}
