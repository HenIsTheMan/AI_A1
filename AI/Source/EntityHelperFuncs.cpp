#include "EntityHelperFuncs.h"

void ChooseRandDir(Entity* const entity, const int gridRows, const int gridCols){
	do{
		switch(Math::RandIntMinMax(0, 3)){
			case 0:
				entity->SetGridTargetLocalPos(entity->GetLocalPos() + Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 1:
				entity->SetGridTargetLocalPos(entity->GetLocalPos() + Vector3(-1.0f, 0.0f, 0.0f));
				break;
			case 2:
				entity->SetGridTargetLocalPos(entity->GetLocalPos() + Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 3:
				entity->SetGridTargetLocalPos(entity->GetLocalPos() + Vector3(0.0f, -1.0f, 0.0f));
				break;
		}
	} while(entity->GetGridTargetLocalPos().x < 0 || entity->GetGridTargetLocalPos().x > gridCols - 1
		|| entity->GetGridTargetLocalPos().y < 0 || entity->GetGridTargetLocalPos().y > gridRows - 1);
}

void MoveInDir(Entity* const entity, const double dt){
	try{
		entity->SetLocalPos(entity->GetLocalPos()
			+ entity->GetSpd() * (entity->GetGridTargetLocalPos() - entity->GetLocalPos()).Normalized() * (float)dt);
	} catch(const DivideByZero&){
		//Do nth
	}
}