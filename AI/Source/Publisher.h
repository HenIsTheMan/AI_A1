#pragma once

#include <unordered_map>

#include "ListenerID.hpp"
#include "ListenerCategory.hpp"
#include "Listener.h"
#include "Singleton.h"

class Publisher final: public Singleton<Publisher>{
	friend Singleton<Publisher>;
public:
	void AddListener(const ListenerID ID, const ListenerCategory category, Listener* const listener);

	int Send(const ListenerID ID, IEvent* myEvent, const bool async = true);
	int MultiSend(const std::initializer_list<ListenerID> IDs, IEvent* myEvent, const bool async = true);
	int GrpSend(const ListenerCategory category, IEvent* myEvent, const bool async = true);
	int Broadcast(IEvent* myEvent, const bool async = true);
private:
	std::unordered_map<ListenerID, Listener*> im_ListenersByID;
	std::unordered_multimap<ListenerCategory, Listener*> im_ListenersByCategory;

	Publisher();
	~Publisher() = default;
};