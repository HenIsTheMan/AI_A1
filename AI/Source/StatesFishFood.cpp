#include "StatesFishFood.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"

StateGrow::StateGrow(const std::string & stateID)
	: State(stateID)
{
}

StateGrow::~StateGrow()
{
}

void StateGrow::Enter(GameObject* go)
{
	go->countDown = 16.0f;
}

void StateGrow::Update(GameObject* go, double dt)
{
	go->countDown -= (float)dt;
	if(go->countDown <= 0.0f){
		go->nextState = go->sm->GetState("StateEvolve");
	}
}

void StateGrow::Exit()
{
}

StateEvolve::StateEvolve(const std::string & stateID)
	: State(stateID)
{
}

StateEvolve::~StateEvolve()
{
}

void StateEvolve::Enter(GameObject* go)
{
	PostOffice::GetInstance()->Send("SceneMovement", new MessageEvolve(go));
	go->active = false;
}

void StateEvolve::Update(GameObject* go, double dt)
{
}

void StateEvolve::Exit()
{
}