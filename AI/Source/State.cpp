#include "State.h"

State::State():
	im_Enter(nullptr),
	im_Update(nullptr),
	im_Exit(nullptr)
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