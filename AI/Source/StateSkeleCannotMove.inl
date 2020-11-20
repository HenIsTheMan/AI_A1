float StateSkeleCannotMove::im_ElapsedTime = 0.0f;
Grid<float>* StateSkeleCannotMove::im_Grid = nullptr;
int StateSkeleCannotMove::im_GridRows = 0;
int StateSkeleCannotMove::im_GridCols = 0;

void StateSkeleCannotMove::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
}

void StateSkeleCannotMove::Update(Entity* const entity, const double dt){
	//* Check for state transition
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();

	if(((int)entityLocalPos.x + 1 < im_GridCols && gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1])
		|| ((int)entityLocalPos.x - 1 >= 0 && gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1])
		|| ((int)entityLocalPos.y + 1 < im_GridRows && gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x])
		|| ((int)entityLocalPos.y - 1 >= 0 && gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x])
	){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateSkeleIdle));
		return;
	}
	//*/

	static float chooseDirBT = 0.0f;
	if(chooseDirBT <= im_ElapsedTime){
		ChooseRandDir(entity);
		chooseDirBT = im_ElapsedTime + Math::RandFloatMinMax(0.9f, 2.0f);
	}
}

void StateSkeleCannotMove::Exit(Entity* const entity){
	entity->SetGridTargetLocalPos(entity->GetLocalPos()); //So will change to valid dir in idle state
}