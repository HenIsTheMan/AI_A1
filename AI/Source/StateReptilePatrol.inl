float StateReptilePatrol::im_ElapsedTime = 0.0f;
Grid<float>* StateReptilePatrol::im_Grid = nullptr;
Publisher* StateReptilePatrol::publisher = Publisher::RetrieveGlobalObjPtr();
Vector3 StateReptilePatrol::im_CommonDirs[2]{Vector3(), Vector3()};

void StateReptilePatrol::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
}

void StateReptilePatrol::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileDead));
		return;
	}

	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
	if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
		entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

		if(Math::RandIntMinMax(1, 4) == 1){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileIdle));
			entity->SetTimeLeft(Math::RandFloatMinMax(2.0f, 5.0f));
		} else if(!ChooseBetween2Dirs(entity, im_Grid, im_CommonDirs)){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileIdle));
			entity->SetTimeLeft(0.0f);
		}
	} else{
		MoveInDir(entity, dt);
	}
}

void StateReptilePatrol::Exit(Entity* const entity){
}