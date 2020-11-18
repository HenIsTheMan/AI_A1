#include "Publisher.h"

#include <cassert>

Publisher::Publisher():
	im_ListenersByID(),
	im_ListenersByCategory()
{
}

void Publisher::AddListener(const ListenerID ID, const ListenerCategory category, Listener* const listener){
	assert(listener && "Var 'listener' must be initialized!");

	if(im_ListenersByID.find(ID) == im_ListenersByID.end()){
		im_ListenersByID.insert(std::pair<ListenerID, Listener*>(ID, listener));
		im_ListenersByCategory.insert(std::pair<ListenerCategory, Listener*>(category, listener));
	}
}

int Publisher::Send(const ListenerID ID, Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	const auto iter = im_ListenersByID.find(ID);

	if(iter == im_ListenersByID.end()){
		delete myEvent;
		myEvent = nullptr;
		return -1;
	}

	Listener* const listener = iter->second;
	if(async){
		listener->AddEvent(myEvent);
		return 1;
	} else{
		return listener->OnEvent(myEvent, true);
	}
}

int Publisher::MultiSend(const std::initializer_list<ListenerID> IDs, Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	int sum = 0;
	for(const auto ID: IDs){
		const auto iter = im_ListenersByID.find(ID);

		if(iter == im_ListenersByID.end()){
			delete myEvent;
			myEvent = nullptr;
			--sum;
			continue;
		}

		Listener* const listener = iter->second;
		if(async){
			listener->AddEvent(myEvent);
			++sum;
		} else{
			sum += listener->OnEvent(myEvent);
		}
	}

	delete myEvent;
	myEvent = nullptr;
	return sum;
}

int Publisher::GrpSend(const ListenerCategory category, Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	if(im_ListenersByCategory.find(category) == im_ListenersByCategory.end()){
		delete myEvent;
		myEvent = nullptr;
		return -1;
	}

	int sum = 0;
	const auto controlIter = im_ListenersByCategory.equal_range(category);
	for(auto iter = controlIter.first; iter != controlIter.second; ++iter){
		Listener* const listener = iter->second;
		if(async){
			listener->AddEvent(myEvent);
			++sum;
		} else{
			sum += listener->OnEvent(myEvent);
		}
	}

	delete myEvent;
	myEvent = nullptr;
	return sum;
}

int Publisher::Broadcast(Event* myEvent, const bool async){
	assert(myEvent && "Var 'myEvent' must be initialized!");

	int sum = 0;
	for(const std::pair<ListenerID, Listener*>& element: im_ListenersByID){
		Listener* const listener = element.second;
		if(async){
			listener->AddEvent(myEvent);
			++sum;
		} else{
			sum += listener->OnEvent(myEvent);
		}
	}

	delete myEvent;
	myEvent = nullptr;
	return sum;
}