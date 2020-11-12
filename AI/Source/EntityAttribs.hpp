#pragma once

#include "Vector3.h"

#include "EntityType.hpp"

struct EntityAttribs final{
	EntityType im_Type = EntityType::Null;
	Vector3 im_LocalPos = Vector3();
	Vector3 im_LocalScale = Vector3();
};