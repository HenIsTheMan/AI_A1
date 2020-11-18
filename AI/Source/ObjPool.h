#pragma once

#include <vector>

template <class T>
class ObjPool final{
public:
	ObjPool<T>();
	~ObjPool<T>();

	void CreateObjs(const int amt);
	void DeactivateObj(const T* const obj);

	T* RetrieveActivatedObj();
	std::vector<std::pair<bool, T*>>& RetrievePool();

	///Getter
	const std::vector<std::pair<bool, T*>>& GetPool() const;
private:
	void ICreateObjs(const int amt); //Internal func

	std::vector<std::pair<bool, T*>> im_ObjPool;
};

#include "ObjPool.inl"