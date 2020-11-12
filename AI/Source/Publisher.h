#pragma once

#include "IListener.hpp"

namespace SDPsWisdomGenesis{
	template <class T>
	class Publisher final{
	public:
		Publisher<T>();
		_5_DEFAULTED(Publisher<T>)

		void AddListener(const IListener<T>* const listener);
		void RemoveListener(const IListener<T>* const listener);
		void Publish(const T* const event);
	private:
		std::vector<IListener<T>*> listeners;
	};
}

#include "Publisher.inl"