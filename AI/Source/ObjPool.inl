template <class T>
ObjPool<T>::ObjPool():
	im_ObjPool()
{
}

template <class T>
ObjPool<T>::~ObjPool(){
	const size_t poolSize = im_ObjPool.size();
	for(size_t i = 0; i < poolSize; ++i){
		T*& obj = im_ObjPool[i].second;
		if(obj){
			delete obj;
			obj = nullptr;
		}
	}
}

template <class T>
void ObjPool<T>::CreateObjs(int amt){
	assert(im_ObjPool.size() == (size_t)0 && "This func shld only be called once");

	ICreateObjs(amt);
}

template <class T>
void ObjPool<T>::DeactivateObj(const T* const obj){
	const size_t poolSize = im_ObjPool.size();
	for(size_t i = 0; i < poolSize; ++i){
		if(im_ObjPool[i].second == obj){
			im_ObjPool[i].first = false;
			break;
		}
	}
}

template <class T>
T* ObjPool<T>::RetrieveActivatedObj(){
	const size_t poolSize = im_ObjPool.size();
	for(size_t i = 0; i < poolSize; ++i){
		if(!im_ObjPool[i].first){
			im_ObjPool[i].first = true;
			return im_ObjPool[i].second;
		}
	}

	im_ObjPool.push_back({false, new T()});
	return im_ObjPool.back().second;
}

template <class T>
std::vector<std::pair<bool, T*>>& ObjPool<T>::RetrievePool(){
	return im_ObjPool;
}

template <class T>
const std::vector<std::pair<bool, T*>>& ObjPool<T>::GetPool() const{
	return im_ObjPool;
}

template <class T>
void ObjPool<T>::ICreateObjs(const int amt){
	im_ObjPool.resize(amt);
	for(int i = 0; i < amt; ++i){
		im_ObjPool[i] = std::make_pair(false, new T());
	}
}