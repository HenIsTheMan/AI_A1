void StateReptileDead::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateReptileDead::Update(Entity* const entity, const double dt){
	entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	if(entity->GetTimeLeft() <= 0.0f){

	}
}

void StateReptileDead::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}