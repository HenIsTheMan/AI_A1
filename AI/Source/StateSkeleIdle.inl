float StateSkeleIdle::im_ElapsedTime = 0.0f;
Grid<float>* StateSkeleIdle::im_Grid = nullptr;
int StateSkeleIdle::im_GridRows = 0;
int StateSkeleIdle::im_GridCols = 0;

void StateSkeleIdle::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateSkeleIdle::Update(Entity* const entity, const double dt){
	//* Check for state transition
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleDead));
		return;
	}

	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
	if(((int)entityLocalPos.x + 1 >= im_GridCols || ((int)entityLocalPos.x + 1 < im_GridCols && gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]))
		&& ((int)entityLocalPos.x - 1 < 0 || ((int)entityLocalPos.x - 1 >= 0 && gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]))
		&& ((int)entityLocalPos.y + 1 >= im_GridRows || ((int)entityLocalPos.y + 1 < im_GridRows && gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]))
		&& ((int)entityLocalPos.y - 1 < 0 || ((int)entityLocalPos.y - 1 >= 0 && gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]))
	){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleCannotMove));
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
				ChooseADir(entity, im_Grid, im_GridRows, im_GridCols);
			}
		} else{
			entity->SetSpriteAniMiddleName("Move");
			MoveInDir(entity, dt);
		}
	} else if(chooseDirBT <= im_ElapsedTime){
		ChooseADir(entity, im_Grid, im_GridRows, im_GridCols);
		chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(0.9f, 2.0f);
	}
	//*/
}

void StateSkeleIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}