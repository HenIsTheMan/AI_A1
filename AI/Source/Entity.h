#pragma once

#include "EntityAttribs.hpp"

namespace Obj{
	template <class T, typename Type>
	class Entity final{
	public:
		Entity<T, Type>();
		Entity<T, Type>(const EntityAttribs<T, Type>& attribs);
		~Entity<T, Type>() = default;

		int& RetrieveStepsLeft();

		//* Getters
		EntityType GetType() const;
		const T& GetLocalPos() const;
		const T& GetLocalScale() const;

		const Type& GetDmg() const;
		const Type& GetRange() const;
		const Type& GetHealth() const;
		const Type& GetSpd() const;

		const Entity<T, Type>* GetTarget() const;
		int GetStepsLeft() const;
		const Type& GetTimeLeft() const;
		const T& GetDir() const;

		const StateMachine<StateID, Entity<T, Type>>* GetStateMachine() const;
		const State* GetCurrState() const;
		const State* GetNextState() const;
		const std::string& GetSpriteAniMiddleName() const;
		//*/

		//* Setters
		void SetType(const EntityType type);
		void SetLocalPos(const T& localPos);
		void SetLocalScale(const T& localScale);

		void SetDmg(const Type& dmg);
		void SetRange(const Type& range);
		void SetHealth(const Type& health);
		void SetSpd(const Type& spd);

		void SetTarget(Entity<T, Type>* const target);
		void SetStepsLeft(const int stepsLeft);
		void SetTimeLeft(const Type& timeLeft);
		void SetDir(const T& dir);

		void SetStateMachine(StateMachine<StateID, Entity<T, Type>>* const stateMachine);
		void SetCurrState(const State* const currState);
		void SetNextState(const State* const nextState);
		void SetSpriteAniMiddleName(const std::string& spriteAniMiddleName);

		#if defined ENTITY_T_IS_VEC3
		void SetLocalPos(const Type& x, const Type& y, const Type& z);
		void SetLocalScale(const Type& x, const Type& y, const Type& z);
		void SetDir(const Type& x, const Type& y, const Type& z);
		#endif
		//*/
	private:
		EntityAttribs<T, Type> im_Attribs;
	};
}

#include "Entity.inl"