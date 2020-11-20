#pragma once

enum struct StateID: int{
	StateSkeleCannotMove,
	StateSkeleIdle,
	StateSkeleAttack,
	StateSkeleDead,
	StateSkeleRevive,

	StateReptileCannotMove,
	StateReptileIdle,
	StateReptileAttack,
	StateReptileDead,
	StateReptileMultiply,

	StateBoyCannotMove,
	StateBoyIdle,
	StateBoyAttack,
	StateBoyDead,
	StateBoyHeal,

	StateOrcCannotMove,
	StateOrcIdle,
	StateOrcAttack,
	StateOrcDead,
	StateOrcImmune,

	Amt
};