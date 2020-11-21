float StateSkeleIdle::im_ElapsedTime = 0.0f;
Grid<float>* StateSkeleIdle::im_Grid = nullptr;
Publisher* StateSkeleIdle::im_Publisher = Publisher::RetrieveGlobalObjPtr();

void StateSkeleIdle::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
	entity->SetSpriteAniElapsedTime(1.0f);
	entity->SetSpriteAniDelay(1.0f);
	entity->SetTarget(nullptr);
}

void StateSkeleIdle::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleDead));
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

	if(im_Publisher->Notify((long int)ListenerFlags::ObjPool, new EventFindClosestEnemy(entity), false)){
		const Entity* const entityTarget = entity->GetTarget();
		const Vector3& entityTargetLocalPos = entityTarget->GetLocalPos();

		const Vector3 vec = Vector3(roundf(entityTargetLocalPos.x), roundf(entityTargetLocalPos.y), roundf(entityTargetLocalPos.z)) - entityLocalPos;
		if(vec.x <= Math::EPSILON && -vec.x <= Math::EPSILON && vec.y <= Math::EPSILON && -vec.y <= Math::EPSILON){ //If both are very close to 0.0f...
			ChooseADir(entity, im_Grid);
			return;
		}

		const Vector3 dir = Vector3(vec.x / fabs(vec.x), vec.y / fabs(vec.y), vec.z);
		const float vecLenSquared = vec.LengthSquared();
		if(vecLenSquared - 1.0f <= Math::EPSILON && 1.0f - vecLenSquared <= Math::EPSILON){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleAttack));
			return;
		}

		if(free){
			if((entityTarget->GetLocalPos() - entityLocalPos).LengthSquared() < 5.0f * 5.0f){
				entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleChase));
				return;
			} else{
				entity->SetTarget(nullptr);
			}
		}
	}

	if(entity->GetTimeLeft() <= 0.0f){
		if(free){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkelePatrol));
			return;
		}
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	}

	static float chooseDirBT = 0.0f;
	if(chooseDirBT <= im_ElapsedTime){
		ChooseRandDir(entity);
		chooseDirBT = im_ElapsedTime + 2.5f;
	}
}

void StateSkeleIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f);
	entity->SetGridTargetLocalPos(entity->GetLocalPos());
}