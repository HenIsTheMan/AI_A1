#pragma once

#include "Vector3.h"

#include "EntityType.hpp"

struct EntityAttribs final{
	EntityType im_Type = EntityType::Null;
	Vector3 im_Pos = Vector3();
	Vector3 im_Scale = Vector3();
};