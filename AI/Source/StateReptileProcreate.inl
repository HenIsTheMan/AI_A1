ObjPool<Entity>* StateReptileProcreate::im_ObjPool = nullptr;

void StateReptileProcreate::Enter(Entity* const entity){
	entity->SetTimeLeft(5.0f);
}

void StateReptileProcreate::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileDead));
		return;
	}

	if(entity->GetTimeLeft() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileAttack));
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	}
}

void StateReptileProcreate::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f);
}