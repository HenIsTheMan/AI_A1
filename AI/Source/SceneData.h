#pragma once

#include "SingletonTemplate.h"

class SceneData final: public Singleton<SceneData>{
	friend Singleton<SceneData>;
public:
	///Getters
	int GetObjCount() const;
	int GetNoGrid() const;
	float GetGridSize() const;
	float GetGridOffset() const;

	///Setters
	void SetObjCount(const int objCount);
	void SetNoGrid(const int noGrid);
	void SetGridSize(const float gridSize);
	void SetGridOffset(const float gridOffset);
private:
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;

	SceneData();
	~SceneData() = default;
};