#pragma once

#include "EntityAttribs.hpp"

namespace Obj{
	template <class T, typename Type>
	class Entity final{
	public:
		Entity<T, Type>();
		Entity<T, Type>(const EntityAttribs<T, Type>& attribs);
		~Entity<T, Type>() = default;

		//* Getters
		EntityType GetType() const;
		const T& GetLocalPos() const;
		const T& GetLocalScale() const;

		const T& GetDir() const;
		const Type& GetSpd() const;
		int GetStepsLeft() const;

		const Type& GetHealth() const;
		const Type& GetTimeLeft() const;
		const Entity<T, Type>* GetTarget() const;

		const StateMachine<StateID, Entity<T, Type>>* GetStateMachine() const;
		const State* GetCurrState() const;
		const State* GetNextState() const;
		//*/

		//* Setters
		void SetType(const EntityType type);
		void SetLocalPos(const T& localPos);
		void SetLocalScale(const T& localScale);

		void SetDir(const T& dir);
		void SetSpd(const Type& spd);
		void SetStepsLeft(const int stepsLeft);

		void SetHealth(const Type& health);
		void SetTimeLeft(const Type& timeLeft);
		void SetTarget(const Entity<T, Type>* const target);

		void SetStateMachine(const StateMachine<StateID, Entity<T, Type>>* const stateMachine);
		void SetCurrState(const State* const currState);
		void SetNextState(const State* const nextState);

		#if defined ENTITY_T_IS_VEC3
		void SetLocalPos(const Type& x, const Type& y, const Type& z);
		void SetLocalScale(const Type& x, const Type& y, const Type& z);
		#endif
		//*/
	private:
		EntityAttribs<T, Type> im_Attribs;
	};
}

#include "Entity.inl"