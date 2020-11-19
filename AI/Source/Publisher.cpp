#include "Publisher.h"

#include <cassert>

Publisher::Publisher():
	im_Listeners()
{
}

void Publisher::AddListener(const long int& flags, Listener* const listener){
	assert(listener && "Var 'listener' must be initialized!");

	im_Listeners.push_back({flags, listener});
}

int Publisher::Send(const long int& flags, Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	for(const std::pair<long int, Listener*>& element: im_Listeners){
		if((long int)element.first & (long int)flags){
			Listener* const listener = element.second;
			if(async){
				listener->AddEvent(myEvent);
				return 1;
			} else{
				return listener->OnEvent(myEvent, true);
			}
		}
	}

	return 0;
}

int Publisher::Broadcast(Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	int sum = 0;
	for(const std::pair<long int, Listener*>& element: im_Listeners){
		Listener* const listener = element.second;
		if(async){
			listener->AddEvent(myEvent->Clone()); //Shallow copy prevented
			++sum;
		} else{
			sum += listener->OnEvent(myEvent);
		}
	}

	delete myEvent;
	myEvent = nullptr;
	return sum;
}