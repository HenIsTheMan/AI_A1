float StateOrcIdle::im_ElapsedTime = 0.0f;
Grid<float>* StateOrcIdle::im_Grid = nullptr;
Publisher* StateOrcIdle::im_Publisher = Publisher::RetrieveGlobalObjPtr();

void StateOrcIdle::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
	entity->SetSpriteAniElapsedTime(1.0f);
	entity->SetSpriteAniDelay(1.0f);
	entity->SetTarget(nullptr);
}

void StateOrcIdle::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcDead));
		return;
	}

	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
	const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();
	const int gridRows = im_Grid->GetRows();
	const int gridCols = im_Grid->GetCols();

	const bool free = ((int)entityLocalPos.x + 1 < gridCols
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
		&& !gridEntityData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]);

	if(free && im_Publisher->Notify((long int)ListenerFlags::ObjPool, new EventFindClosestEnemy(entity), false)){
		const Entity* const entityTarget = entity->GetTarget();

		if((entityTarget->GetLocalPos() - entityLocalPos).LengthSquared() < 3.0f * 3.0f){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcChase));
			return;
		} else{
			entity->SetTarget(nullptr);
		}
	}

	if(entity->GetTimeLeft() <= 0.0f){
		if(free){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcPatrol));
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

void StateOrcIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f);
	entity->SetGridTargetLocalPos(entity->GetLocalPos());
}