#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include <vector>

#include "SceneBase.h"
#include "Entity.h"
#include "Grid.h"
#include "ObjPool.h"

class SceneMovement final: public SceneBase{
public:
	SceneMovement();
	~SceneMovement();

	void Update(double dt) override;
	void Render() override;
protected:
	float gridCellWidth;
	float gridCellHeight;
	float gridLineThickness;
	int gridRows;
	int gridCols;
	Grid<float> grid;

	bool isDay;
	float dayNightBT;
	ObjPool<Entity>* objPool;

	void UpdateGridData();
	void UpdateGridProperties();
	void UpdateEntities();

	void RenderGrid();
	void RenderGridBG();
	void RenderEntities();
	void RenderTranslucentBlock();
	void RenderBG();
	void RenderSceneText();
};

#endif