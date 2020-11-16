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
//#include "StateID.hpp" //Shld be here instead
#include "Entity.h"
#include "StateMachine.h"

using Entity = Obj::Entity<Vector3, float>; //Can because Entity<Vector3, float> is in another namespace
using SM = StateMachine<StateID, Entity>;

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
	ObjPool<Entity>* objPool;

	//* Shared SMs
	SM* skeleSM;
	SM* reptileSM;
	SM* boySM;
	SM* orcSM;
	//*/

	Entity* CreateSkele() const;
	Entity* CreateReptile() const;
	Entity* CreateBoy() const;
	Entity* CreateOrc() const;

	void UpdateGridData();
	void UpdateGridProperties();
	void UpdateEntities();

	void RenderGrid();
	void RenderGridBG();
	void RenderGridData();
	void RenderEntities();
	void RenderAnimatedEntities(const Entity* const entity);
	void RenderTranslucentBlock();
	void RenderBG();
	void RenderSceneText();
};