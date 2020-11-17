#include "EntityHelperFuncs.h"

void ChooseRandDir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols){
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridData = grid->GetData();
	std::vector<Vector3> possibleLocations;

	if((int)entityLocalPos.x + 1 < gridCols && !gridData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]){
		possibleLocations.emplace_back(entityLocalPos + Vector3(1.0f, 0.0f, 0.0f));
	}
	if((int)entityLocalPos.x - 1 >= 0 && !gridData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]){
		possibleLocations.emplace_back(entityLocalPos - Vector3(1.0f, 0.0f, 0.0f));
	}
	if((int)entityLocalPos.y + 1 < gridRows && !gridData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]){
		possibleLocations.emplace_back(entityLocalPos + Vector3(0.0f, 1.0f, 0.0f));
	}
	if((int)entityLocalPos.y - 1 >= 0 && !gridData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]){
		possibleLocations.emplace_back(entityLocalPos - Vector3(0.0f, 1.0f, 0.0f));
	}

	const size_t possibleLocationsSize = possibleLocations.size();
	if(possibleLocationsSize){
		entity->SetGridTargetLocalPos(possibleLocations[Math::RandIntMinMax(0, possibleLocationsSize - 1)]);

		if(entity->GetTimeLeft() > 999.0f){
			entity->SetTimeLeft(0.0f);
		}
	} else{
		entity->SetSpriteAniMiddleName("Static");
		entity->SetTimeLeft(1000.0f);

		switch(Math::RandIntMinMax(0, 3)){
			case 0:
				entity->SetGridTargetLocalPos(entityLocalPos + Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 1:
				entity->SetGridTargetLocalPos(entityLocalPos - Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 2:
				entity->SetGridTargetLocalPos(entityLocalPos + Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 3:
				entity->SetGridTargetLocalPos(entityLocalPos - Vector3(0.0f, 1.0f, 0.0f));
				break;
		}
	}
}

void MoveInDir(Entity* const entity, const double dt){
	entity->SetLocalPos(entity->GetLocalPos()
		+ entity->GetSpd() * (entity->GetGridTargetLocalPos() - entity->GetLocalPos()).Normalized() * (float)dt);
}