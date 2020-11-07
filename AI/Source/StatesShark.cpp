#include "StatesShark.h"

StateCrazy::StateCrazy(const std::string & stateID)
	: State(stateID)
{
}

StateCrazy::~StateCrazy()
{
}

void StateCrazy::Enter(GameObject* go)
{
	go->moveSpeed = 25.0f;
}

void StateCrazy::Update(GameObject* go, double dt)
{
}

void StateCrazy::Exit()
{
}


StateNaughty::StateNaughty(const std::string & stateID)
	: State(stateID)
{
}

StateNaughty::~StateNaughty()
{
}

void StateNaughty::Enter(GameObject* go)
{
	go->moveSpeed = 15.f;
}

void StateNaughty::Update(GameObject* go, double dt)
{
}

void StateNaughty::Exit()
{
}


StateHappy::StateHappy(const std::string & stateID)
	: State(stateID)
{
}

StateHappy::~StateHappy()
{
}

void StateHappy::Enter(GameObject* go)
{
	go->moveSpeed = 10.0f;
}

void StateHappy::Update(GameObject* go, double dt)
{
}

void StateHappy::Exit()
{
}