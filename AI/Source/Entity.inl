namespace Obj{
	template <class T>
	Entity<T>::Entity():
		Entity(EntityAttribs<T>())
	{
	}

	template <class T>
	Entity<T>::Entity(const EntityAttribs<T>& attribs):
		im_Attribs(attribs)
	{
	}

	template <class T>
	T& Entity<T>::RetrieveLocalPos(){
		return im_Attribs.im_LocalPos;
	}

	template <class T>
	T& Entity<T>::RetrieveLocalScale(){
		return im_Attribs.im_LocalScale;
	}

	template <class T>
	const EntityType& Entity<T>::GetType() const{
		return im_Attribs.im_Type;
	}

	template <class T>
	const T& Entity<T>::GetLocalPos() const{
		return im_Attribs.im_LocalPos;
	}

	template <class T>
	const T& Entity<T>::GetLocalScale() const{
		return im_Attribs.im_LocalScale;
	}

	template <class T>
	void Entity<T>::SetType(const EntityType type){
		im_Attribs.im_Type = type;
	}

	template <class T>
	void Entity<T>::SetLocalPos(const T& localPos){
		im_Attribs.im_LocalPos = localPos;
	}

	template <class T>
	void Entity<T>::SetLocalScale(const T& localScale){
		im_Attribs.im_LocalScale = localScale;
	}

	#if defined ENTITY_T_IS_VEC3
	template <class T>
	void Entity<T>::SetLocalPos(const float x, const float y, const float z){
		im_Attribs.im_LocalPos = T(x, y, z);
	}

	template <class T>
	void Entity<T>::SetLocalScale(const float x, const float y, const float z){
		im_Attribs.im_LocalScale = T(x, y, z);
	}
	#endif
}