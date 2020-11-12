#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include <vector>

///Shld be done in client's PCH
#ifndef ENTITY_T_IS_VEC3
	#define ENTITY_T_IS_VEC3
#endif

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
	ObjPool<Obj::Entity<Vector3>>* objPool;

	void UpdateGridData();
	void UpdateGridProperties();
	void UpdateEntities();

	void RenderGrid();
	void RenderGridBG();
	void RenderGridData();
	void RenderEntities();
	void RenderTranslucentBlock();
	void RenderBG();
	void RenderSceneText();
};

#endif