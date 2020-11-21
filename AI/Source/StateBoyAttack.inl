void StateBoyAttack::Enter(Entity* const entity){
	entity->SetSpriteAniMiddleName("Move");
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
}

void StateBoyAttack::Exit(Entity* const entity){
}