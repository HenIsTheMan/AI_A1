#pragma once

enum struct EventID: int{
	EventBlockPlaced,
	EventAttacking,
	EventGridHeightShrinking,
	EventGridWidthShrinking,
	EventCalcActiveObjs,
	EventCalcInactiveObjs,
	EventCalcAlphaCount,
	EventCalcOmegaCount,
	EventFindClosestEnemy,
	Amt
};