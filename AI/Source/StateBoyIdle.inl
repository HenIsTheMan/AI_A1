Grid<float>* StateBoyIdle::im_Grid = nullptr;
int StateBoyIdle::im_GridRows = 0;
int StateBoyIdle::im_GridCols = 0;

void StateBoyIdle::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateBoyIdle::Update(Entity* const entity, const double dt){
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();

	if(entity->GetTimeLeft() <= 0.0f){
		if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(entityGridTargetLocalPos); //Snap entity's local pos

			if(Math::RandIntMinMax(1, 100) <= 50){
				entity->SetSpriteAniMiddleName("Static");
				entity->SetTimeLeft((float)Math::RandIntMinMax(2, 5));
			} else{
				entity->SetSpriteAniMiddleName("Move");
				ChooseRandDir(entity, im_Grid, im_GridRows, im_GridCols);
			}
		} else{
			entity->SetSpriteAniMiddleName("Move");
			MoveInDir(entity, dt);
		}
	} else{
		entity->SetSpriteAniMiddleName("Static");

		if(entity->GetTimeLeft() < 999.0f){
			entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
		}

		if(Math::RandIntMinMax(1, 500) == 1){
			ChooseRandDir(entity, im_Grid, im_GridRows, im_GridCols);
		}
	}
}

void StateBoyIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}