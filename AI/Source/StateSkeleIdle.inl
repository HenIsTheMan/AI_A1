void StateSkeleIdle::Enter(Entity* const entity){
}

void StateSkeleIdle::Update(Entity* const entity, const double dt){
	int& entityStepsLeft = entity->RetrieveStepsLeft();

	if(!entityStepsLeft){
		switch(Math::RandIntMinMax(0, 3)){
			case 0:
				entity->SetDir(Vector3(1.0f, 0.0f, 0.0f));
				break;
			case 1:
				entity->SetDir(Vector3(-1.0f, 0.0f, 0.0f));
				break;
			case 2:
				entity->SetDir(Vector3(0.0f, 1.0f, 0.0f));
				break;
			case 3:
				entity->SetDir(Vector3(0.0f, -1.0f, 0.0f));
				break;
		}

		entityStepsLeft = 60;
	} else{
		--entityStepsLeft;
	}
}

void StateSkeleIdle::Exit(Entity* const entity){
}