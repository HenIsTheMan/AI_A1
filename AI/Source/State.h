#ifndef STATE_H
#define STATE_H

#include <string>

struct GameObject;

class State
{
	const std::string m_stateID;
protected:
	State(const std::string& stateID);
public:
	virtual ~State() = default;
	const std::string& GetStateID() const;

	virtual void Enter(GameObject* go) = 0;
	virtual void Update(GameObject* go, double dt) = 0;
	virtual void Exit() = 0;
};

#endif