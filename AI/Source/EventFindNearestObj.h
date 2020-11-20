#pragma once

#include "Event.h"

#include "EntityTeam.hpp"

class EventFindNearestObj final: public Event{
	EventFindNearestObj() = delete;
public:
	EventFindNearestObj(const EntityTeam team);
	~EventFindNearestObj() = default;

	///Getter
	EntityTeam GetTeam() const;
private:
	EntityTeam im_Team;

	EventFindNearestObj* Clone() const override;
};