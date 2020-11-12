#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include "Message.h"

class ObjectBase{ //Abstract class
public:
	virtual bool Handle(Message* message, const bool destroyMsg = false) = 0;

	bool AddMessage(Message* const message){
		try{
			messages.emplace(message);
			return true;
		} catch(...){
			assert(false);
			return false;
		}
	}

	Message* FetchMessage(){
		if(!messages.empty()){
			Message* message = messages.front();
			messages.pop();
			return message;
		} else{
			return nullptr;
		}
	}
protected:
	ObjectBase():
		messages()
	{
	}

	virtual ~ObjectBase(){
		while(!messages.empty()){
			Message*& message = messages.front();
			if(message){
				delete message;
				message = nullptr;
			}
			messages.pop();
		}
	}

	std::queue<Message*> messages;
};

#endif