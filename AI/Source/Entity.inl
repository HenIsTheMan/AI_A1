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
	T& Entity<T, Type>::RetrieveLocalPos(){
		return im_Attribs.im_LocalPos;
	}

	template <class T, typename Type>
	T& Entity<T, Type>::RetrieveLocalScale(){
		return im_Attribs.im_LocalScale;
	}

	template <class T, typename Type>
	const EntityType& Entity<T, Type>::GetType() const{
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

	#if defined ENTITY_T_IS_VEC3
	template <class T, typename Type>
	void Entity<T, Type>::SetLocalPos(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_LocalPos = T(x, y, z);
	}

	template <class T, typename Type>
	void Entity<T, Type>::SetLocalScale(const Type& x, const Type& y, const Type& z){
		im_Attribs.im_LocalScale = T(x, y, z);
	}
	#endif
}