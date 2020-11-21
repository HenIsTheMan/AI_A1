Grid<float>* StateBoyChase::im_Grid = nullptr;
Publisher* StateBoyChase::im_Publisher = Publisher::RetrieveGlobalObjPtr();

void StateBoyChase::Enter(Entity* const entity){
}

void StateBoyChase::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	if(im_Publisher->Notify((long int)ListenerFlags::ObjPool, new EventFindClosestEnemy(entity), false)){
		const Entity* const entityTarget = entity->GetTarget();
		const Vector3& entityTargetLocalPos = entityTarget->GetLocalPos();
		const Vector3& entityLocalPos = entity->GetLocalPos();
		const Vector3& entityGridTargetLocalPos = entity->GetGridTargetLocalPos();

		if((entityGridTargetLocalPos - entityLocalPos).Length() < entity->GetSpd() * (float)dt){
			entity->SetLocalPos(roundf(entityGridTargetLocalPos.x), roundf(entityGridTargetLocalPos.y), roundf(entityGridTargetLocalPos.z)); //Snap entity's local pos

			const Vector3 vec = Vector3(roundf(entityTargetLocalPos.x), roundf(entityTargetLocalPos.y), roundf(entityTargetLocalPos.z)) - entityLocalPos;
			const Vector3 dir = Vector3(vec.x / fabs(vec.x), vec.y / fabs(vec.y), vec.z);
			const float vecLenSquared = vec.LengthSquared();
			if(vecLenSquared - 1.0f <= Math::EPSILON && 1.0f - vecLenSquared <= Math::EPSILON){
				entity->SetSpriteAniMiddleName("Static");
				return;
			}

			Vector3 newGridTargetLocalPos;
			if(fabs(vec.x) > fabs(vec.y)){
				newGridTargetLocalPos = entityLocalPos + Vector3(dir.x, 0.0f, 0.0f);
			} else{
				newGridTargetLocalPos = entityLocalPos + Vector3(0.0f, dir.y, 0.0f);
			}

			const std::vector<std::vector<bool>>& gridBlockData = im_Grid->GetBlockData();
			const std::vector<std::vector<bool>>& gridEntityData = im_Grid->GetEntityData();

			if(!gridBlockData[(int)newGridTargetLocalPos.y][(int)newGridTargetLocalPos.x]
				&& !gridEntityData[(int)newGridTargetLocalPos.y][(int)newGridTargetLocalPos.x]
			){ //If grid cell is empty...
				entity->SetSpriteAniMiddleName("Move");
				entity->SetGridTargetLocalPos(newGridTargetLocalPos);
			} else{
				entity->SetSpriteAniMiddleName("Static");
			}
		} else{
			MoveInDir(entity, dt);
		}
	} else{
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyPatrol));
		return;
	}
}

void StateBoyChase::Exit(Entity* const entity){
}