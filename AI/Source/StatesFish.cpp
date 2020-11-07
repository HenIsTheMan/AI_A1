#include "StatesFish.h"

#include <vector>

StateTooFull::StateTooFull(const std::string & stateID)
	: State(stateID)
{
}

StateTooFull::~StateTooFull()
{
}

void StateTooFull::Enter(GameObject* go)
{
	go->target = go->pos; //Stationary
}

void StateTooFull::Update(GameObject* go, double dt)
{
	go->energy -= 1.f * (float)dt; //Energy slowly drops

	if(go->energy < 10.0f){
		go->nextState = go->sm->GetState("StateFull");
	}
}

void StateTooFull::Exit()
{
}


StateFull::StateFull(const std::string & stateID)
	: State(stateID)
{
}

StateFull::~StateFull()
{
}

void StateFull::Enter(GameObject* go)
{
	go->moveSpeed = 7.0f; //Move at a high spd
}

void StateFull::Update(GameObject* go, double dt)
{
	go->energy -= 1.f * (float)dt; //Energy slowly drops

	if(go->energy < 5.0f){
		go->nextState = go->sm->GetState("StateHungry");
	}
	if(go->energy >= 10.0f){
		go->nextState = go->sm->GetState("StateTooFull");
	}
}

void StateFull::Exit()
{
}


StateHungry::StateHungry(const std::string & stateID)
	: State(stateID)
{
}

StateHungry::~StateHungry()
{
}

void StateHungry::Enter(GameObject* go)
{
	go->moveSpeed = 4.8f; //Move at a normal spd
}

void StateHungry::Update(GameObject* go, double dt)
{
	go->energy -= 1.f * (float)dt; //Energy slowly drops

	if(go->energy <= 0.0f){
		go->nextState = go->sm->GetState("StateDead");
	}
	if(go->energy >= 5.0f){
		go->nextState = go->sm->GetState("StateFull");
	}
}

void StateHungry::Exit()
{
}


StateDead::StateDead(const std::string & stateID)
	: State(stateID)
{
}

StateDead::~StateDead()
{
}

void StateDead::Enter(GameObject* go)
{
	go->target = go->pos; //Stationary
}

void StateDead::Update(GameObject* go, double dt)
{
}

void StateDead::Exit()
{
}