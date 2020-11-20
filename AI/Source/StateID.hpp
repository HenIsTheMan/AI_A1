#pragma once

enum struct StateID: int{
	StateSkeleIdle,
	StateSkelePatrol,
	StateSkeleAttack,
	StateSkeleDead,
	StateSkeleChase,

	StateReptileIdle,
	StateReptilePatrol,
	StateReptileAttack,
	StateReptileDead,
	StateReptileChase,

	StateBoyIdle,
	StateBoyPatrol,
	StateBoyAttack,
	StateBoyDead,
	StateBoyChase,

	StateOrcIdle,
	StateOrcPatrol,
	StateOrcAttack,
	StateOrcDead,
	StateOrcChase,

	Amt
};