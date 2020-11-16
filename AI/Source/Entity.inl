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
	const T& Entity<T, Type>::GetDir() const{
		return im_Attribs.im_Dir;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetSpd() const{
		return im_Attribs.im_Spd;
	}

	template <class T, typename Type>
	int Entity<T, Type>::GetStepsLeft() const{
		return im_Attribs.im_StepsLeft;
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
	const Type& Entity<T, Type>::GetHealth() const{
		return im_Attribs.im_Health;
	}

	template <class T, typename Type>
	const Type& Entity<T, Type>::GetTimeLeft() const{
		return im_Attribs.im_TimeLeft;
	}

	template <class T, typename Type>
	const Entity<T, Type>* Entity<T, Type>::GetTarget() const{
		return im_Attribs.im_Target;
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
	void Entity<T, Type>::SetDir(const T& dir){
		im_Attribs.im_Dir = dir;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetSpd(const Type& spd){
		im_Attribs.im_Spd = spd;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetStepsLeft(const int stepsLeft){
		im_Attribs.im_StepsLeft = stepsLeft;
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
	void Entity<T, Type>::SetHealth(const Type& health){
		im_Attribs.im_Health = health;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetTimeLeft(const Type& timeLeft){
		im_Attribs.im_TimeLeft = timeLeft;
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetTarget(Entity<T, Type>* const target){
		im_Attribs.im_Target = target;
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
	void Entity<T, Type>::SetDir(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_Dir = T(x, y, z);
	}
	#endif
}