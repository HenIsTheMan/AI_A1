#pragma once

#include "EntityAttribs.hpp"

namespace Obj{
	template <class T, typename Type>
	class Entity final{
	public:
		Entity<T, Type>();
		Entity<T, Type>(const EntityAttribs<T, Type>& attribs);
		~Entity<T, Type>() = default;

		T& RetrieveLocalPos();
		T& RetrieveLocalScale();

		///Getters
		const EntityType& GetType() const;
		const T& GetLocalPos() const;
		const T& GetLocalScale() const;

		///Setters
		void SetType(const EntityType type);
		void SetLocalPos(const T& localPos);
		void SetLocalScale(const T& localScale);

		#if defined ENTITY_T_IS_VEC3
		void SetLocalPos(const Type& x, const Type& y, const Type& z);
		void SetLocalScale(const Type& x, const Type& y, const Type& z);
		#endif
	private:
		EntityAttribs<T, Type> im_Attribs;
	};
}

#include "Entity.inl"