#pragma once

#include "Entity.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

void ChooseRandDir(Entity* const entity);
void MoveInDir(Entity* const entity, const double dt);