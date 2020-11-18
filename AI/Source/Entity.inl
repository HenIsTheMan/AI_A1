#include "EventGridDataChanged.h"

namespace Obj{
	template <class T, typename Type>
	Entity<T, Type>::Entity():
		Entity(EntityAttribs<T, Type>())
	{
	}

	template <class T, typename Type>
	Entity<T, Type>::Entity(const EntityAttribs<T, Type>& attribs):
		im_Attribs(attribs)
	{
	}

	template <class T, typename Type>
	int Entity<T, Type>::OnEvent(const Event* myEvent, const bool destroyEvent){
		if(!myEvent){
			return -1;
		}

		switch(myEvent->GetID()){
			case EventID::EventGridDataChanged: {
				const EventGridDataChanged* const eventGridDataChanged = dynamic_cast<const EventGridDataChanged*>(myEvent);
				assert(eventGridDataChanged && "Val of eventGridDataChanged is nullptr!");

				const float blockRow = (float)eventGridDataChanged->GetBlockRow();
				const float blockCol = (float)eventGridDataChanged->GetBlockCol();

				if(im_Attribs.im_LocalPos.x > blockCol - 1.0f || im_Attribs.im_LocalPos.x < blockCol + 1.0f
					|| im_Attribs.im_LocalPos.y > blockRow - 1.0f || im_Attribs.im_LocalPos.y < blockRow + 1.0f){
					//eventGridDataChanged->im_ObjPool->DeactivateObj(this);
				}
				break;
			}
		}

		if(destroyEvent && myEvent){
			delete myEvent;
			myEvent = nullptr;
		}
		return -1;
	}

	template <class T, typename Type>
	EntityType Entity<T, Type>::GetType() const{
		return im_Attribs.im_Type;
	}

	template <class T, typename Type>
	const T& Entity<T, Type>::GetLocalPos() const{
		return im_Attribs.im_LocalPos;
	}

	template <class T, typename Type>
	const T& Entity<T, Type>::GetLocalScale() const{
		return im_Attribs.im_LocalScale;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetDmg() const{
		return im_Attribs.im_Dmg;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetRange() const{
		return im_Attribs.im_Range;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetCurrHealth() const{
		return im_Attribs.im_CurrHealth;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetMaxHealth() const{
		return im_Attribs.im_MaxHealth;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetSpd() const{
		return im_Attribs.im_Spd;
	}

	template <class T, typename Type>
	const Entity<T, Type>* Entity<T, Type>::GetTarget() const{
		return im_Attribs.im_Target;
	}

	template <class T, typename Type>
	const T& Entity<T, Type>::GetGridTargetLocalPos() const{
		return im_Attribs.im_GridTargetLocalPos;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetTimeLeft() const{
		return im_Attribs.im_TimeLeft;
	}

	template <class T, typename Type>
	const StateMachine<StateID, Entity<T, Type>>* Entity<T, Type>::GetStateMachine() const{
		return im_Attribs.im_StateMachine;
	}

	template <class T, typename Type>
	const State* Entity<T, Type>::GetCurrState() const{
		return im_Attribs.im_CurrState;
	}

	template <class T, typename Type>
	const State* Entity<T, Type>::GetNextState() const{
		return im_Attribs.im_NextState;
	}

	template <class T, typename Type>
	const std::string& Entity<T, Type>::GetSpriteAniMiddleName() const{
		return im_Attribs.im_SpriteAniMiddleName;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetType(const EntityType type){
		im_Attribs.im_Type = type;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetLocalPos(const T& localPos){
		im_Attribs.im_LocalPos = localPos;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetLocalScale(const T& localScale){
		im_Attribs.im_LocalScale = localScale;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetDmg(const Type& dmg){
		im_Attribs.im_Dmg = dmg;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetRange(const Type& range){
		im_Attribs.im_Range = range;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetCurrHealth(const Type& currHealth){
		im_Attribs.im_CurrHealth = currHealth;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetMaxHealth(const Type& maxHealth){
		im_Attribs.im_MaxHealth = maxHealth;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetSpd(const Type& spd){
		im_Attribs.im_Spd = spd;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetTarget(Entity<T, Type>* const target){
		im_Attribs.im_Target = target;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetGridTargetLocalPos(const T& gridTargetLocalPos){
		im_Attribs.im_GridTargetLocalPos = gridTargetLocalPos;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetTimeLeft(const Type& timeLeft){
		im_Attribs.im_TimeLeft = timeLeft;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetStateMachine(StateMachine<StateID, Entity<T, Type>>* const stateMachine){
		im_Attribs.im_StateMachine = stateMachine;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetCurrState(const State* const currState){
		im_Attribs.im_CurrState = const_cast<State* const>(currState);
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetNextState(const State* const nextState){
		im_Attribs.im_NextState = const_cast<State* const>(nextState);
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetSpriteAniMiddleName(const std::string& spriteAniMiddleName){
		im_Attribs.im_SpriteAniMiddleName = spriteAniMiddleName;
	}

	#if defined ENTITY_T_IS_VEC3
	template <class T, typename Type>
	void Entity<T, Type>::SetLocalPos(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_LocalPos = T(x, y, z);
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetLocalScale(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_LocalScale = T(x, y, z);
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetGridTargetLocalPos(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_GridTargetLocalPos = T(x, y, z);
	}
	#endif
}