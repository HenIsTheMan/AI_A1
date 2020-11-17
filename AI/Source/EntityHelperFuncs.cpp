#include "EntityHelperFuncs.h"

void ChooseRandDir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols){
	Vector3& gridTargetLocalPos = entity->RetrieveGridTargetLocalPos();

	do{
		switch(Math::RandIntMinMax(0, 3)){
			case 0:
				gridTargetLocalPos = entity->GetLocalPos() + Vector3(1.0f, 0.0f, 0.0f);
				break;
			case 1:
				gridTargetLocalPos = entity->GetLocalPos() + Vector3(-1.0f, 0.0f, 0.0f);
				break;
			case 2:
				gridTargetLocalPos = entity->GetLocalPos() + Vector3(0.0f, 1.0f, 0.0f);
				break;
			case 3:
				gridTargetLocalPos = entity->GetLocalPos() + Vector3(0.0f, -1.0f, 0.0f);
				break;
		}
	} while(gridTargetLocalPos.x < 0 || gridTargetLocalPos.x > gridCols - 1
		|| gridTargetLocalPos.y < 0 || gridTargetLocalPos.y > gridRows - 1);
}

void MoveInDir(Entity* const entity, const double dt){
	entity->SetLocalPos(entity->GetLocalPos()
		+ entity->GetSpd() * (entity->GetGridTargetLocalPos() - entity->GetLocalPos()).Normalized() * (float)dt);
}