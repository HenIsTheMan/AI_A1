#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue):
	type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	sm(nullptr),
	currState(nullptr),
	nextState(nullptr)
{
}

GameObject::~GameObject(){
	sm = nullptr;
	currState = nullptr;
	nextState = nullptr;
}

void GameObject::SetNextState(){
	if(nextState != currState){
		if(currState){
			currState->Exit();
		}
		currState = nextState;
		if(currState){
			currState->Enter(this);
		}
	}
}