#pragma once

#include <vector>

template <class T>
class ObjPool final{
public:
	ObjPool<T>();
	~ObjPool<T>();

	const std::vector<std::pair<bool, T*>>& GetObjPool() const;
	T* RetrieveInactiveObj();
	void CreateObjs(int amt);
private:
	std::vector<std::pair<bool, T*>> im_ObjPool;
};

#include "ObjPool.inl"