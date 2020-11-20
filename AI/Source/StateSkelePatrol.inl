float StateSkelePatrol::im_ElapsedTime = 0.0f;
Grid<float>* StateSkelePatrol::im_Grid = nullptr;
Publisher* StateSkelePatrol::publisher = Publisher::RetrieveGlobalObjPtr();

void StateSkelePatrol::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
}

void StateSkelePatrol::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleDead));
		return;
	}

	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
	if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
		entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

		if(Math::RandIntMinMax(1, 4) == 1){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleIdle));
			entity->SetTimeLeft(Math::RandFloatMinMax(2.0f, 5.0f));
		} else if(!ChooseADir(entity, im_Grid)){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleIdle));
			entity->SetTimeLeft(0.0f);
		}
	} else{
		MoveInDir(entity, dt);
	}
}

void StateSkelePatrol::Exit(Entity* const entity){
}