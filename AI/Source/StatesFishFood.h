#pragma once

#include "StateMachine.h"

class StateGrow final: public State{
public:
	StateGrow(const std::string &stateID);
	~StateGrow();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};

class StateEvolve final: public State{
public:
	StateEvolve(const std::string &stateID);
	~StateEvolve();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};