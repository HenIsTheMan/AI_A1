ObjPool<Entity>* StateSkeleDead::im_ObjPool = nullptr;

void StateSkeleDead::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateSkeleDead::Update(Entity* const entity, const double dt){
	entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	if(entity->GetTimeLeft() <= 0.0f){
		im_ObjPool->DeactivateObj(entity);
	}
}

void StateSkeleDead::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}