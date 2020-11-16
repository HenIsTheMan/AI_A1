#include "State.h"

State::State():
	State(StateID::Amt, nullptr, nullptr, nullptr)
{
}

State::State(const StateID ID, void (* const enter)(), void (* const update)(const double dt), void (* const exit)()):
	im_ID(ID),
	im_Enter(enter),
	im_Update(update),
	im_Exit(exit)
{
}

StateID State::GetID() const{
	return im_ID;
}

void State::SetID(const StateID ID){
	im_ID = ID;
}

void State::SetEnter(void (* const enter)()){
	im_Enter = enter;
}

void State::SetUpdate(void (* const update)(const double dt)){
	im_Update = update;
}

void State::SetExit(void (* const exit)()){
	im_Exit = exit;
}

void State::Enter() const{
	if(im_Enter){
		im_Enter();
	}
}

void State::Update(const double dt) const{
	if(im_Update){
		im_Update(dt);
	}
}

void State::Exit() const{
	if(im_Exit){
		im_Exit();
	}
}