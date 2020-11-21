void StateBoyChase::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
}

void StateBoyChase::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	const Entity* const entityTarget = entity->GetTarget();
	if(entityTarget){
		const Vector3& entityGridTargetLocalPos = entity->GetGridTargetLocalPos();
		const Vector3& entityLocalPos = entity->GetLocalPos();
		const Vector3& entityTargetLocalPos = entityTarget->GetLocalPos();

		if((entityGridTargetLocalPos - entityLocalPos).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

			const Vector3 vec = entityTargetLocalPos - entityLocalPos;

			///??
			const Vector3 dir = vec.Normalized();
			if(fabs(vec.x) > fabs(vec.y)){
				entity->SetGridTargetLocalPos(entityGridTargetLocalPos + Vector3((entityTargetLocalPos.x < entityLocalPos.x ? -dir.x : dir.x), 0.0f, 0.0f));
			} else{
				entity->SetGridTargetLocalPos(entityGridTargetLocalPos + Vector3(0.0f, (entityTargetLocalPos.y < entityLocalPos.y ? -dir.y : dir.y), 0.0f));
			}
		} else{
			MoveInDir(entity, dt);
		}
	} else{
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyIdle));
		return;
	}
}

void StateBoyChase::Exit(Entity* const entity){
}