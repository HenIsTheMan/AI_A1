#pragma once

#include "EntityAttribs.hpp"

namespace Obj{
	template <class T>
	class Entity final{
	public:
		Entity<T>();
		Entity<T>(const EntityAttribs<T>& attribs);
		~Entity<T>() = default;

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
		void SetLocalPos(const float x, const float y, const float z);
		void SetLocalScale(const float x, const float y, const float z);
		#endif
	private:
		EntityAttribs<T> im_Attribs;
	};
}

#include "Entity.inl"