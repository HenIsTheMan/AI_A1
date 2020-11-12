#include "StatesFish.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"

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
	go->nearest = nullptr;
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
	go->nearest = nullptr;
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

	static float sendBT = 0.0f;
	static float inStateTime = 0.0f;

	inStateTime += (float)dt;
	if(sendBT <= inStateTime){
		PostOffice::GetInstance()->Send("SceneMovement", new MessageWRU(go, MessageWRU::NEAREST_SHARK, 150.0f));
		sendBT = inStateTime + 1.0f;
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
	go->nearest = nullptr;

	PostOffice::GetInstance()->Send("SceneMovement", new MessageSpawnFood(go));
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

	if(!go->nearest || (go->nearest && !go->nearest->active)){
		if(PostOffice::GetInstance()->Send("SceneMovement", new MessageWRU(go, MessageWRU::NEAREST_FISHFOOD, 150.0f), false)){
			(void)PostOffice::GetInstance()->Broadcast(new MessageStop(go));
		}
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
	go->nearest = nullptr;
}

void StateDead::Update(GameObject* go, double dt)
{
}

void StateDead::Exit()
{
}