void StateBoyImmune::Enter(Entity* const entity){
}

void StateBoyImmune::Update(Entity* const entity, const double dt){
}

void StateBoyImmune::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}