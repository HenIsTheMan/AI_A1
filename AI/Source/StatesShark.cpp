#include "StatesShark.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"

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
	go->nearest = nullptr;
}

void StateCrazy::Update(GameObject* go, double dt)
{
	if(!go->nearest || (go->nearest && (!go->nearest->active || go->nearest->currState->GetStateID() == "StateDead"))){
		PostOffice::GetInstance()->Send("SceneMovement", new MessageWRU(go, MessageWRU::HIGHEST_ENERGYFISH, 5.0f));
	}
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
	go->nearest = nullptr;
}

void StateNaughty::Update(GameObject* go, double dt)
{
	if(!go->nearest || (go->nearest && !go->nearest->active)){
		PostOffice::GetInstance()->Send("SceneMovement", new MessageWRU(go, MessageWRU::NEAREST_FULLFISH, 5.0f));
	}
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
	go->nearest = nullptr;

	PostOffice::GetInstance()->Send("SceneMovement", new MessageSpawnFish(go));
}

void StateHappy::Update(GameObject* go, double dt)
{
}

void StateHappy::Exit()
{
}