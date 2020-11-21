void StateBoyChase::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
}

void StateBoyChase::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	const Entity* const entityTarget = entity->GetTarget();
	if(entityTarget){
	} else{
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyIdle));
		return;
	}
}

void StateBoyChase::Exit(Entity* const entity){
}