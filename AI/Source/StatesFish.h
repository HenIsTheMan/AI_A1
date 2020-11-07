#ifndef STATES_FISH_H
#define STATES_FISH_H

#include "StateMachine.h"

class StateTooFull final: public State{
public:
	StateTooFull(const std::string &stateID);
	~StateTooFull();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};

class StateFull final: public State{
public:
	StateFull(const std::string &stateID);
	~StateFull();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};

class StateHungry final: public State{
public:
	StateHungry(const std::string &stateID);
	~StateHungry();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};

class StateDead final: public State{
public:
	StateDead(const std::string &stateID);
	~StateDead();

	virtual void Enter(GameObject* go) override;
	virtual void Update(GameObject* go, double dt) override;
	virtual void Exit() override;
};

#endif