ObjPool<Entity>* StateOrcDead::im_ObjPool = nullptr;

void StateOrcDead::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateOrcDead::Update(Entity* const entity, const double dt){
	entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	if(entity->GetTimeLeft() <= 0.0f){
		im_ObjPool->DeactivateObj(entity);
	}
}

void StateOrcDead::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}