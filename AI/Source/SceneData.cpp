#include "SceneData.h"

int SceneData::GetObjCount() const{
	return m_objectCount;
}

int SceneData::GetNoGrid() const{
	return m_noGrid;
}

float SceneData::GetGridSize() const{
	return m_gridSize;
}

float SceneData::GetGridOffset() const{
	return m_gridOffset;
}

void SceneData::SetObjCount(const int objCount){
	m_objectCount = objCount;
}

void SceneData::SetNoGrid(const int noGrid){
	m_noGrid = noGrid;
}

void SceneData::SetGridSize(const float gridSize){
	m_gridSize = gridSize;
}

void SceneData::SetGridOffset(const float gridOffset){
	m_gridOffset = gridOffset;
}

SceneData::SceneData():
	m_objectCount(0),
	m_noGrid(0),
	m_gridSize(0.0f),
	m_gridOffset(0.0f)
{
}