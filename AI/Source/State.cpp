#include "State.h"

State::State():
	State(nullptr, nullptr, nullptr)
{
}

State::State(void (* const enter)(), void (* const update)(const double dt), void (* const exit)()):
	im_Enter(enter),
	im_Update(update),
	im_Exit(exit)
{
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

void State::Enter(){
	if(im_Enter){
		im_Enter();
	}
}

void State::Update(const double dt){
	if(im_Update){
		im_Update(dt);
	}
}

void State::Exit(){
	if(im_Exit){
		im_Exit();
	}
}