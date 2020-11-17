int StateSkeleIdle::im_GridRows = 0;
int StateSkeleIdle::im_GridCols = 0;

void StateSkeleIdle::Enter(Entity* const entity){
}

void StateSkeleIdle::Update(Entity* const entity, const double dt){
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();

	if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
		entity->SetLocalPos(entityGridTargetLocalPos); //Snap entity's local pos

		ChooseRandDir(entity, im_GridRows, im_GridCols);
	} else{
		MoveInDir(entity, dt);

		entity->SetSpriteAniMiddleName("Move");
	}
}

void StateSkeleIdle::Exit(Entity* const entity){
}