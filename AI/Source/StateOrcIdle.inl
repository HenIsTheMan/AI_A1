Grid<float>* StateOrcIdle::im_Grid = nullptr;
int StateOrcIdle::im_GridRows = 0;
int StateOrcIdle::im_GridCols = 0;

void StateOrcIdle::Enter(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}

void StateOrcIdle::Update(Entity* const entity, const double dt){
	//* Check for state transition
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcDead));
		return;
	}
	//*/

	//* Update entity
	const Vector3 entityGridTargetLocalPos = entity->GetGridTargetLocalPos();

	if(entity->GetTimeLeft() <= 0.0f){
		if((entityGridTargetLocalPos - entity->GetLocalPos()).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

			entity->SetSpriteAniMiddleName("Move");
			ChooseRandDir(entity, im_Grid, im_GridRows, im_GridCols);
		} else{
			entity->SetSpriteAniMiddleName("Move");
			MoveInDir(entity, im_Grid, im_GridRows, im_GridCols, dt);
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
	//*/
}

void StateOrcIdle::Exit(Entity* const entity){
	entity->SetTimeLeft(0.0f); //Just in case
}