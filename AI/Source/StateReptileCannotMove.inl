float StateReptileCannotMove::im_ElapsedTime = 0.0f;
Grid<float>* StateReptileCannotMove::im_Grid = nullptr;
int StateReptileCannotMove::im_GridRows = 0;
int StateReptileCannotMove::im_GridCols = 0;

void StateReptileCannotMove::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
}

void StateReptileCannotMove::Update(Entity* const entity, const double dt){
	//* Check for state transition
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
	const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();

	if(((int)entityLocalPos.x + 1 < im_GridCols
		&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]
		&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1])
		|| ((int)entityLocalPos.x - 1 >= 0
		&& !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]
		&& !gridEntityData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1])
		|| ((int)entityLocalPos.y + 1 < im_GridRows
		&& !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]
		&& !gridEntityData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x])
		|| ((int)entityLocalPos.y - 1 >= 0
		&& !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]
		&& !gridEntityData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x])
	){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateReptileIdle));
		return;
	}
	//*/

	static float chooseDirBT = 0.0f;
	if(chooseDirBT <= im_ElapsedTime){
		ChooseRandDir(entity);
		chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(0.9f, 2.0f);
	}
}

void StateReptileCannotMove::Exit(Entity* const entity){
	entity->SetGridTargetLocalPos(entity->GetLocalPos()); //So will change to valid dir in idle state
}