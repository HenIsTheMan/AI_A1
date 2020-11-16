#pragma once

#include "Vector3.h"

#include "EntityType.hpp"
#include "State.h"

enum struct StateID: int;

template <class T, typename Type>
class StateMachine;

namespace Obj{
	template <class T, typename Type>
	class Entity;

	template <class T, typename Type>
	struct EntityAttribs final{
		EntityAttribs<T, Type>() = default;
		~EntityAttribs<T, Type>() = default;

		EntityType im_Type = EntityType::Null;
		T im_LocalPos = T();
		T im_LocalScale = T();

		T im_Dir = T();
		Type im_Spd = Type();
		int im_StepsLeft = 0;

		Type im_Dmg = Type();
		Type im_Range = Type();
		Type im_Health = Type();
		Type im_TimeLeft = Type();
		Entity<T, Type>* im_Target = nullptr;

		StateMachine<StateID, Entity<T, Type>>* im_StateMachine = nullptr;
		State* im_CurrState = nullptr;
		State* im_NextState = nullptr;
	};
}