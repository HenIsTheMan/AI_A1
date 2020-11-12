#pragma once

#include "Vector3.h"

#include "EntityType.hpp"

namespace Obj{
	template <class T>
	struct EntityAttribs final{
		EntityAttribs<T>() = default;
		~EntityAttribs<T>() = default;

		EntityType im_Type = EntityType::Null;
		T im_LocalPos = T();
		T im_LocalScale = T();
	};
}