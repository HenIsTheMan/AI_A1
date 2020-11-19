#pragma once

#ifndef BIT
	#define BIT(x) 1 << x
#endif

enum struct ListenerFlags: long int{ //Flags enum
	ObjPool = BIT(1),
	Skele = BIT(2),
	Reptile = BIT(3),
	Boy = BIT(4),
	Orc = BIT(5),
	Entity = BIT(6),
	Amt = 6
};