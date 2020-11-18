#include "Event.h"

Event::Event():
	Event(EventID::Amt)
{
}

Event::Event(const EventID ID):
	im_ID(ID)
{
}