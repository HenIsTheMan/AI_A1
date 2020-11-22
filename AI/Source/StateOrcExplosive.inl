void StateOrcExplosive::Enter(Entity* const entity){
	entity->SetMaxHealth(30.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
}

void StateOrcExplosive::Update(Entity* const entity, const double dt){
}

void StateOrcExplosive::Exit(Entity* const entity){
	if(entity->GetNextState()->GetID() == StateID::StateSkeleIdle){
		entity->SetMaxHealth(150.0f);
		entity->SetCurrHealth(entity->GetMaxHealth());
	}
}