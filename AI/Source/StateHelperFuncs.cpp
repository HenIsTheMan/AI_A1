#include "StateHelperFuncs.h"

bool ChooseADir(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols){
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
	if(!possibleLocationsSize){
		return false;
	}
	entity->SetGridTargetLocalPos(possibleLocations[Math::RandIntMinMax(0, possibleLocationsSize - 1)]);
	return true;
}

bool ChooseBetween2Dirs(Entity* const entity, const Grid<float>* const grid, const int gridRows, const int gridCols, const Vector3(&commonDirs)[2]){
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
		entity->SetGridTargetLocalPos(entityLocalPos + *possibleDir);
		return true;
	}
	
	return false;
}

void ChooseRandDir(Entity* const entity){
	const Vector3 possibleDirs[4]{
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f)
	};
	entity->SetGridTargetLocalPos(entity->GetLocalPos() + possibleDirs[Math::RandIntMinMax(0, 3)]);
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

void MoveInDir(Entity* const entity, const double dt){
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const Vector3 entityDir = (entity->GetGridTargetLocalPos() - entityLocalPos).Normalized();
	entity->SetLocalPos(entityLocalPos + entity->GetSpd() * entityDir * (float)dt);
}