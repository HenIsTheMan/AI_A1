void StateSkeleIdle::Enter(Entity* const entity){
}

void StateSkeleIdle::Update(Entity* const entity, const double dt){
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();

	if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
		entity->SetLocalPos(entityGridTargetLocalPos); //Snap entity's local pos

		ChooseRandDir(entity);
	} else{
		MoveInDir(entity, dt);

		entity->SetSpriteAniMiddleName("Move");
	}
}

void StateSkeleIdle::Exit(Entity* const entity){
}