void StateSkeleDeadButNotDead::Enter(Entity* const entity){
	entity->SetMaxHealth(180.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
}

void StateSkeleDeadButNotDead::Update(Entity* const entity, const double dt){
}

void StateSkeleDeadButNotDead::Exit(Entity* const entity){
	if(entity->GetNextState()->GetID() == StateID::StateSkeleIdle){
		entity->SetMaxHealth(45.0f);
		entity->SetCurrHealth(entity->GetMaxHealth());
	}
}