#include "StateHelperFuncs.h"

void ChooseRandDir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols){
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = grid->GetBlockData();
	std::vector<Vector3> possibleLocations;

	if((int)entityLocalPos.x + 1 < gridCols && !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]){
		possibleLocations.emplace_back(entityLocalPos + Vector3(1.0f, 0.0f, 0.0f));
	}
	if((int)entityLocalPos.x - 1 >= 0 && !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]){
		possibleLocations.emplace_back(entityLocalPos - Vector3(1.0f, 0.0f, 0.0f));
	}
	if((int)entityLocalPos.y + 1 < gridRows && !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]){
		possibleLocations.emplace_back(entityLocalPos + Vector3(0.0f, 1.0f, 0.0f));
	}
	if((int)entityLocalPos.y - 1 >= 0 && !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]){
		possibleLocations.emplace_back(entityLocalPos - Vector3(0.0f, 1.0f, 0.0f));
	}

	const size_t possibleLocationsSize = possibleLocations.size();
	if(possibleLocationsSize){
		entity->SetGridTargetLocalPos(possibleLocations[Math::RandIntMinMax(0, possibleLocationsSize - 1)]);

		if(entity->GetTimeLeft() > 999.0f){
			entity->SetTimeLeft(0.0f);
		}
	} else{
		entity->SetTimeLeft(1000.0f);
	}
}

void ChooseBetween2Dirs(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols, const Vector3(&commonDirs)[2]){
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = grid->GetBlockData();
	const Vector3* possibleDir = nullptr;

	for(int index = 0; index < 2; ++index){
		const int i = int(rand() % 2 ? index == 0 : index == 1);

		if((commonDirs[i].x > 0.0f && (int)entityLocalPos.x + 1 < gridCols && !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1])
			|| (commonDirs[i].x < 0.0f && (int)entityLocalPos.x - 1 >= 0 && !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1])
			|| (commonDirs[i].y > 0.0f && (int)entityLocalPos.y + 1 < gridRows && !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x])
			|| (commonDirs[i].y < 0.0f && (int)entityLocalPos.y - 1 >= 0 && !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x])
		){
			possibleDir = &commonDirs[i];
		}

		if(!possibleDir){
			continue;
		}

		entity->SetSpriteAniMiddleName("Move");
		entity->SetGridTargetLocalPos(entityLocalPos + *possibleDir);

		if(entity->GetTimeLeft() > 999.0f){
			entity->SetTimeLeft(0.0f);
		}
		return;
	}
	entity->SetTimeLeft(1000.0f);
}

void ChooseRandPairOfPerpendicularDirs(Vector3 (&commonDirs)[2]){
	switch(Math::RandIntMinMax(0, 3)){
		case 0:
			commonDirs[0] = Vector3(0.0f, 1.0f, 0.0f);
			commonDirs[1] = Vector3(-1.0f, 0.0f, 0.0f);
			break;
		case 1:
			commonDirs[0] = Vector3(0.0f, 1.0f, 0.0f);
			commonDirs[1] = Vector3(1.0f, 0.0f, 0.0f);
			break;
		case 2:
			commonDirs[0] = Vector3(0.0f, -1.0f, 0.0f);
			commonDirs[1] = Vector3(-1.0f, 0.0f, 0.0f);
			break;
		case 3:
			commonDirs[0] = Vector3(0.0f, -1.0f, 0.0f);
			commonDirs[1] = Vector3(1.0f, 0.0f, 0.0f);
			break;
	}
}

void MoveInDir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols, const double dt){
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const Vector3 entityDir = (entity->GetGridTargetLocalPos() - entityLocalPos).Normalized();
	const std::vector<std::vector<bool>>& gridBlockData = grid->GetBlockData();

	const int rowIndex = int(entityLocalPos.y + entityDir.y);
	const int colIndex = int(entityLocalPos.x + entityDir.x);

	if(!gridBlockData[rowIndex][colIndex]){
		entity->SetLocalPos(entityLocalPos + entity->GetSpd() * entityDir * (float)dt);
	} else{
		entity->SetTimeLeft(1000.0f);
	}
}