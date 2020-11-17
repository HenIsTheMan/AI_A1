Grid<float>* StateReptileIdle::im_Grid = nullptr;
int StateReptileIdle::im_GridRows = 0;
int StateReptileIdle::im_GridCols = 0;
Vector3 StateReptileIdle::im_CommonDirs[2]{Vector3(), Vector3()};

void StateReptileIdle::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateReptileIdle::Update(Entity* const entity, const double dt){
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
	const Vector3 entityLocalPos = entity->GetLocalPos();

	if(entity->GetTimeLeft() <= 0.0f){
		if((entityGridTargetLocalPos - entityLocalPos).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(entityGridTargetLocalPos); //Snap entity's local pos

			if(Math::RandIntMinMax(1, 100) <= 10){
				entity->SetSpriteAniMiddleName("Static");
				entity->SetTimeLeft((float)Math::RandIntMinMax(2, 5));
			} else{
				entity->SetSpriteAniMiddleName("Move");
				ChooseBetween2Dirs(entity, im_Grid, im_GridRows, im_GridCols, im_CommonDirs);
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
			ChooseBetween2Dirs(entity, im_Grid, im_GridRows, im_GridCols, im_CommonDirs);
		}
	}
}

void StateReptileIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}