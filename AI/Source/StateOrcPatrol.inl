float StateOrcPatrol::im_ElapsedTime = 0.0f;
Grid<float>* StateOrcPatrol::im_Grid = nullptr;
Publisher* StateOrcPatrol::im_Publisher = Publisher::RetrieveGlobalObjPtr();

void StateOrcPatrol::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
}

void StateOrcPatrol::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcDead));
		return;
	}

	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
	if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
		entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

		if(Math::RandIntMinMax(1, 4) == 1){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcIdle));
			entity->SetTimeLeft(Math::RandFloatMinMax(2.0f, 5.0f));
		} else if(!ChooseADir(entity, im_Grid)){
			entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcIdle));
			entity->SetTimeLeft(0.0f);
		}
	} else{
		MoveInDir(entity, dt);
	}
}

void StateOrcPatrol::Exit(Entity* const entity){
}