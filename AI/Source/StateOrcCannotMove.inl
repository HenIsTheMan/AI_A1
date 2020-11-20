float StateOrcCannotMove::im_ElapsedTime = 0.0f;
Grid<float>* StateOrcCannotMove::im_Grid = nullptr;

void StateOrcCannotMove::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
}

void StateOrcCannotMove::Update(Entity* const entity, const double dt){
	//* Check for state transition
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
	const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();
	const int gridRows = im_Grid->GetRows();
	const int gridCols = im_Grid->GetCols();

	if(((int)entityLocalPos.x + 1 < gridCols
		&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]
		&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1])
		|| ((int)entityLocalPos.x - 1 >= 0
		&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]
		&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1])
		|| ((int)entityLocalPos.y + 1 < gridRows
		&& !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]
		&& !gridEntityData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x])
		|| ((int)entityLocalPos.y - 1 >= 0
		&& !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]
		&& !gridEntityData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x])
	){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateOrcPatrol));
		return;
	}
	//*/

	static float chooseDirBT = 0.0f;
	if(chooseDirBT <= im_ElapsedTime){
		ChooseRandDir(entity);
		chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(0.9f, 2.0f);
	}
}

void StateOrcCannotMove::Exit(Entity* const entity){
	entity->SetGridTargetLocalPos(entity->GetLocalPos());
}