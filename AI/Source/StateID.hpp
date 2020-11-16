#pragma once

enum struct StateID: int{
	StateSkeleIdle,
	StateSkeleAttack,
	StateSkeleDead,
	StateSkeleRevive,

	StateReptileIdle,
	StateReptileAttack,
	StateReptileDead,
	StateReptileMultiply,

	StateBoyIdle,
	StateBoyAttack,
	StateBoyDead,
	StateBoyHeal,

	StateOrcIdle,
	StateOrcAttack,
	StateOrcDead,
	StateOrcImmune,

	Amt
};