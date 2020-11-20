#pragma once

enum struct StateID: int{
	StateSkeleCannotMove,
	StateSkelePatrol,
	StateSkeleAttack,
	StateSkeleDead,
	StateSkeleRevive,

	StateReptileCannotMove,
	StateReptilePatrol,
	StateReptileAttack,
	StateReptileDead,
	StateReptileMultiply,

	StateBoyCannotMove,
	StateBoyPatrol,
	StateBoyAttack,
	StateBoyDead,
	StateBoyHeal,

	StateOrcCannotMove,
	StateOrcPatrol,
	StateOrcAttack,
	StateOrcDead,
	StateOrcImmune,

	Amt
};