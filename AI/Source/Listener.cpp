#include "Listener.h"

void Listener::AddEvent(IEvent* const myEvent){
	events.emplace(myEvent);
}

const IEvent* Listener::FetchEvent(){
	if(!events.empty()){
		IEvent* myEvent = events.front();
		events.pop();
		return myEvent;
	} else{
		return nullptr;
	}
}

Listener::Listener():
	events()
{
}

Listener::~Listener(){
	while(!events.empty()){
		IEvent*& myEvent = events.front();
		if(myEvent){
			delete myEvent;
			myEvent = nullptr;
		}
		events.pop();
	}
};