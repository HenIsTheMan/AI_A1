float StateBoyIdle::im_ElapsedTime = 0.0f;
Grid<float>* StateBoyIdle::im_Grid = nullptr;

void StateBoyIdle::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
}

void StateBoyIdle::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	if(entity->GetTimeLeft() <= 0.0f){
		const Vector3& entityLocalPos = entity->GetLocalPos();
		const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
		const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();
		const int gridRows = im_Grid->GetRows();
		const int gridCols = im_Grid->GetCols();

		if(((int)entityLocalPos.x + 1 < gridCols
			&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]
			&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1])
			|| ((int)entityLocalPos.x - 1 >= 0
			&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]
			&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1])
			|| ((int)entityLocalPos.y + 1 < gridRows
			&& !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]
			&& !gridEntityData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x])
			|| ((int)entityLocalPos.y - 1 >= 0
			&& !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]
			&& !gridEntityData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x])
			){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyPatrol));
			return;
		}
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	}

	static float chooseDirBT = 0.0f;
	if(chooseDirBT <= im_ElapsedTime){
		ChooseRandDir(entity);
		chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(1.5f, 2.9f);
	}
}

void StateBoyIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f);
	entity->SetGridTargetLocalPos(entity->GetLocalPos());
}