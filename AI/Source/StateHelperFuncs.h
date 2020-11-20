#pragma once

#include <vector>

#include "Entity.h" //In case not included before
#include "Grid.h" //In case not included before
#include "ObjPool.h" //In case not included before

using Entity = Obj::Entity<Vector3, float>;

bool ChooseADir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols);
void ChooseRandDir(Entity* const entity);
bool ChooseBetween2Dirs(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols, const Vector3 (&commonDirs)[2]);
void ChooseRandPairOfPerpendicularDirs(Vector3 (&commonDirs)[2]);

void MoveInDir(Entity* const entity, const double dt);