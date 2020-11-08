#include "State.h"

State::State(const std::string& stateID)
	: im_stateID(stateID)
{
}

const std::string& State::GetStateID() const
{
	return im_stateID;
}