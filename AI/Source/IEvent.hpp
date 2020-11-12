#pragma once

#include "Wisdom.h"

namespace SDPsWisdomGenesis{
	class IEvent{
	public:
		virtual ~IEvent() = default;
		_4_DEFAULTED(IEvent)
	protected:
		IEvent() = default;
	};
}