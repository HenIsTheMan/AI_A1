#include "PostOffice.h"

void PostOffice::Register(const std::string & address, ObjectBase * object){
	if (!object)
		return;
	if (m_addressBook.find(address) != m_addressBook.end())
		return;
	m_addressBook.insert(std::pair<std::string, ObjectBase*>(address, object));
}

bool PostOffice::Send(const std::string & address, Message * message, const bool async){
	if(!message){
		return false;
	}

	std::map<std::string, ObjectBase*>::iterator it = m_addressBook.find(address);
	if(m_addressBook.find(address) == m_addressBook.end()){
		delete message;
		return false;
	}

	ObjectBase *object = (ObjectBase*)it->second;
	if(async){
		return object->AddMessage(message);
	} else{
		return object->Handle(message, true);
	}
}

int PostOffice::Broadcast(Message* message, const bool async){
	if(!message){
		return 0;
	}

	int amtOfSuccesses = 0;
	if(async){
		for(auto& element: m_addressBook){
			ObjectBase* object = element.second;
			amtOfSuccesses += (int)object->AddMessage(new Message(*message));
		}

		delete message;
		message = nullptr;
	} else{
		for(auto& element : m_addressBook){
			ObjectBase* object = element.second;
			amtOfSuccesses += (int)object->Handle(message);
		}

		delete message;
		message = nullptr;
	}
	return amtOfSuccesses;
}