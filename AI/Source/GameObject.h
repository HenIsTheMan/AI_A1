#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "State.h"

#pragma warning(push)
#pragma warning(disable: 26485)
#pragma warning(disable: 26495)
#pragma warning(disable: 26812)

class StateMachine;

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CROSS,
		GO_CIRCLE,

		GO_FISH,
		GO_SHARK,
		GO_FISHFOOD,

		GO_TOTAL
	};

	float energy;
	float moveSpeed;
	float countDown;

	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	float mass;
	Vector3 target;
	int id;
	int steps;

	StateMachine *sm;
	State *currState;
	State *nextState;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void SetNextState();
};

#endif