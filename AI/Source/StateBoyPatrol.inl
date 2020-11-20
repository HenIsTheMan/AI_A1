float StateBoyPatrol::im_ElapsedTime = 0.0f;
Grid<float>* StateBoyPatrol::im_Grid = nullptr;

void StateBoyPatrol::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateBoyPatrol::Update(Entity* const entity, const double dt){
	//* Check for state transition
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
	const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();
	const int gridRows = im_Grid->GetRows();
	const int gridCols = im_Grid->GetCols();

	if(((int)entityLocalPos.x + 1 >= gridCols || ((int)entityLocalPos.x + 1 < gridCols
		&& gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]
		&& gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]))
		&& ((int)entityLocalPos.x - 1 < 0 || ((int)entityLocalPos.x - 1 >= 0
		&& gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]
		&& gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]))
		&& ((int)entityLocalPos.y + 1 >= gridRows || ((int)entityLocalPos.y + 1 < gridRows
		&& gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]
		&& gridEntityData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]))
		&& ((int)entityLocalPos.y - 1 < 0 || ((int)entityLocalPos.y - 1 >= 0
		&& gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]
		&& gridEntityData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]))
	){
		std::cout << "Wow 4!\n";
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyCannotMove));
		return;
	}
	//*/

	//* Update entity
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
	static float goStopBT = 0.0f;
	static float chooseDirBT = 0.0f;

	if(entity->GetTimeLeft() <= 0.0f){
		if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

			if(goStopBT <= im_ElapsedTime && Math::RandIntMinMax(1, 10) == 1){
				entity->SetSpriteAniMiddleName("Static");
				entity->SetTimeLeft((float)Math::RandIntMinMax(3, 6));
				goStopBT = im_ElapsedTime + 0.5f;
			} else{
				entity->SetSpriteAniMiddleName("Move");
				ChooseADir(entity, im_Grid);
			}
		} else{
			entity->SetSpriteAniMiddleName("Move");
			MoveInDir(entity, dt);
		}
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);

		if(entity->GetTimeLeft() <= 0.0f){
			ChooseADir(entity, im_Grid);
		} else if(chooseDirBT <= im_ElapsedTime){
			ChooseRandDir(entity);
			chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(1.2f, 2.5f);
		}
	}
	//*/
}

void StateBoyPatrol::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}