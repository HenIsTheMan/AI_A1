#pragma once

#include "Vector3.h"

#include "EntityType.hpp"
#include "State.h"

namespace Obj{
	template <class T>
	struct EntityAttribs final{
		EntityAttribs<T>() = default;
		~EntityAttribs<T>() = default;

		EntityType im_Type = EntityType::Null;
		T im_LocalPos = T();
		T im_LocalScale = T();

		StateMachine* im_StateMachine = nullptr;
		State* im_CurrState = nullptr;
		State* im_NextState = nullptr;


		float energy;
		float moveSpeed;
		float countDown;

		Vector3 vel;
		float mass;
		Vector3 target;
		int id;
		int steps;

		GameObject* nearest;
	};
}