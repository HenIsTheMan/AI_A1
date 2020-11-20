Grid<float>* StateBoyCannotMove::im_Grid = nullptr;

void StateBoyCannotMove::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Static");
}

void StateBoyCannotMove::Update(Entity* const entity, const double dt){
	//* Check for state transition
	const Vector3& entityLocalPos = entity->GetLocalPos();
	const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();

	if(!gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x + 1]
		|| !gridBlockData[(int)entityLocalPos.y][(int)entityLocalPos.x - 1]
		|| !gridBlockData[(int)entityLocalPos.y + 1][(int)entityLocalPos.x]
		|| !gridBlockData[(int)entityLocalPos.y - 1][(int)entityLocalPos.x]
	){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyIdle));
		return;
	}
	//*/

	ChooseRandDir(entity);
}

void StateBoyCannotMove::Exit(Entity* const entity){
}