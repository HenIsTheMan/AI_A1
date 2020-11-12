//#ifndef CONCRETE_MESSAGE_H
//#define CONCRETE_MESSAGE_H
//
//#include "Message.h"
//#include "GameObject.h"
//
//struct MessageWRU final: public Message{
//	enum SEARCH_TYPE{
//		SEARCH_NONE = 0,
//		NEAREST_SHARK,
//		NEAREST_FISHFOOD,
//		NEAREST_FULLFISH,
//		HIGHEST_ENERGYFISH,
//	};
//	MessageWRU(GameObject *goValue, SEARCH_TYPE typeValue, float thresholdValue) : go(goValue), type(typeValue), threshold(thresholdValue) {}
//	~MessageWRU() = default;
//
//	GameObject *go;
//	SEARCH_TYPE type;
//	float threshold;
//};
//
//struct MessageCheckActive final: public Message{
//	MessageCheckActive() = default;
//	~MessageCheckActive() = default;
//};
//
//struct MessageCheckFish final: public Message{
//	MessageCheckFish() = default;
//	~MessageCheckFish() = default;
//};
//
//struct MessageKillAllGOs final: public Message{
//	MessageKillAllGOs() = default;
//	~MessageKillAllGOs() = default;
//};
//
//struct MessageKillAllFish final: public Message{
//	MessageKillAllFish() = default;
//	~MessageKillAllFish() = default;
//};
//
//struct MessageKillAllSharks final: public Message{
//	MessageKillAllSharks() = default;
//	~MessageKillAllSharks() = default;
//};
//
//struct MessageKillAllFood final: public Message{
//	MessageKillAllFood() = default;
//	~MessageKillAllFood() = default;
//};
//
//struct MessageSpawnFood final: public Message{
//	MessageSpawnFood(GameObject *goValue):
//		go(goValue)
//	{
//	}
//	~MessageSpawnFood() = default;
//
//	GameObject *go;
//};
//
//struct MessageStop final: public Message{
//	MessageStop(GameObject *goValue):
//		go(goValue)
//	{
//	}
//	~MessageStop() = default;
//
//	GameObject *go;
//};
//
//struct MessageSpawnFish final: public Message{
//	MessageSpawnFish(GameObject *goValue):
//		go(goValue)
//	{
//	}
//	~MessageSpawnFish() = default;
//
//	GameObject *go;
//};
//
//struct MessageEvolve final: public Message{
//	MessageEvolve(GameObject *goValue):
//		go(goValue)
//	{
//	}
//	~MessageEvolve() = default;
//
//	GameObject *go;
//};
//
//#endif