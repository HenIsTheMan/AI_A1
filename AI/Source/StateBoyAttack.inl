void StateBoyAttack::Enter(Entity* const entity){
}

void StateBoyAttack::Update(Entity* const entity, const double dt){
	if(entity->GetCurrHealth() <= 0.0f){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyDead));
		return;
	}

	const Vector3& entityTargetLocalPos = entity->GetTarget()->GetLocalPos();
	const Vector3 vec = Vector3(roundf(entityTargetLocalPos.x), roundf(entityTargetLocalPos.y), roundf(entityTargetLocalPos.z)) - entity->GetLocalPos();
	const float vecLenSquared = vec.LengthSquared();
	if(!(vecLenSquared - 1.0f <= Math::EPSILON && 1.0f - vecLenSquared <= Math::EPSILON)){
		entity->SetNextState(entity->GetStateMachine()->GetState(StateID::StateBoyChase));
		return;
	}

	if(entity->GetTimeLeft() <= 0.0f){
		if(entity->GetSpriteAniMiddleName() == "Slash"){
			entity->SetSpriteAniMiddleName("Static");

			entity->SetTimeLeft(1.0f); //Attack cooldown
		} else{
			entity->SetSpriteAniMiddleName("Slash");
			//Send msg??

			entity->SetTimeLeft(0.4f); //Attack interval
		}
	} else{
		entity->SetTimeLeft(entity->GetTimeLeft() - (float)dt);
	}
	entity->SetGridTargetLocalPos(entity->GetLocalPos() + vec); //No need to normalize as not moving there
}

void StateBoyAttack::Exit(Entity* const entity){
	entity->SetGridTargetLocalPos(entity->GetLocalPos());
}