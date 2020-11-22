void StateSkeleDeadButNotDead::Enter(Entity* const entity){
	entity->SetMaxHealth(160.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
	entity->SetTimeLeft(8.0f);
}

void StateSkeleDeadButNotDead::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleDead));
		return;
	}

	if(entity->GetTimeLeft() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleIdle));
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	}
}

void StateSkeleDeadButNotDead::Exit(Entity* const entity){
	if(entity->GetNextState()->GetID() == StateID::StateSkeleIdle){
		entity->SetMaxHealth(45.0f);
		entity->SetCurrHealth(entity->GetMaxHealth());
		entity->SetTimeLeft(0.0f);
	}
}