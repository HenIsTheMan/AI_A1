#pragma once

#include "StateID.hpp" //Shld not be here

class State final{ //Shld be templated
public:
	State();
	State(const StateID ID, void (* const enter)(), void (* const update)(const double dt), void (* const exit)());
	~State() = default;

	void Enter() const;
	void Update(const double dt) const;
	void Exit() const;

	///Getter
	StateID GetID() const;

	///Setters
	void SetID(const StateID ID);
	void SetEnter(void (* const enter)());
	void SetUpdate(void (* const update)(const double dt));
	void SetExit(void (* const exit)());
private:
	StateID im_ID;

	void (*im_Enter)();
	void (*im_Update)(const double dt);
	void (*im_Exit)();
};