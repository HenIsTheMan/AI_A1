#pragma once

#include <vector>

///Shld be done in client's PCH
#ifndef ENTITY_T_IS_VEC3
	#define ENTITY_T_IS_VEC3
#endif

#include "SceneSupport.h"
#include "Grid.h"
#include "ObjPool.h"

///In this order
#include "Entity.h"
#include "StateID.hpp"
#include "StateMachine.h"

class Scene final: public SceneSupport{
public:
	Scene();
	~Scene();

	void Update(double dt) override;
	void Render() override;
protected:
	float gridCellWidth;
	float gridCellHeight;
	float gridLineThickness;
	int gridRows;
	int gridCols;
	int gridMinRows;
	int gridMinCols;
	int gridMaxRows;
	int gridMaxCols;
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