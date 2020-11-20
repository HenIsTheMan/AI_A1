#pragma once

enum struct StateID: int{
	StateSkeleIdle,
	StateSkelePatrol,
	StateSkeleAttack,
	StateSkeleDead,
	StateSkeleRevive,

	StateReptileIdle,
	StateReptilePatrol,
	StateReptileAttack,
	StateReptileDead,
	StateReptileMultiply,

	StateBoyIdle,
	StateBoyPatrol,
	StateBoyAttack,
	StateBoyDead,
	StateBoyHeal,

	StateOrcIdle,
	StateOrcPatrol,
	StateOrcAttack,
	StateOrcDead,
	StateOrcImmune,

	Amt
};