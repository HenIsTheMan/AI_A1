#pragma once

#include <vector>

template <class T>
class ObjPool final{
public:
	ObjPool<T>();
	~ObjPool<T>();

	T* RetrieveInactiveObj();
	void CreateObjs(int amt);

	std::vector<std::pair<bool, T*>>& RetrievePool();

	///Getter
	const std::vector<std::pair<bool, T*>>& GetPool() const;
private:
	std::vector<std::pair<bool, T*>> im_ObjPool;
};

#include "ObjPool.inl"