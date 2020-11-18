void StateBoyDead::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateBoyDead::Update(Entity* const entity, const double dt){
	entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	if(entity->GetTimeLeft() <= 0.0f){
		
	}
}

void StateBoyDead::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}