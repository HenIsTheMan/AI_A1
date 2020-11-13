#pragma once

class IEvent{
public:
	virtual ~IEvent() = default;
protected:
	IEvent() = default;
};