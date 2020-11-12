namespace SDPsWisdomGenesis{
	template <class T>
	Publisher<T>::Publisher():
		listeners()
	{
	}

	template <class T>
	void Publisher<T>::AddListener(const IListener<T>* const listener){
		listeners.emplace_back(listener);
	}

	template <class T>
	void Publisher<T>::RemoveListener(const IListener<T>* const listener){
		std::vector<IListener*>::iterator iter = std::find(listeners.begin(), listeners.end(), listener);
		iter != listeners.end() ? (void)listeners.erase(iter) : WARNING_LOG("IListener to be removed cannot be found in Publisher!");
	}

	template <class T>
	void Publisher<T>::Publish(const T* const event){
		for(IListener<T>* const listener: listeners){
			listener->OnEvent(event);
		}
	}
}