#include "State.h"

State::State(const std::string& stateID)
	: m_stateID(stateID)
{
}

const std::string& State::GetStateID() const
{
	return m_stateID;
}