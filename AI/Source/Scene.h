#pragma once

#include <vector>

///Shld be done in client's PCH
#ifndef ENTITY_T_IS_VEC3
	#define ENTITY_T_IS_VEC3
#endif

#include "ListenerFlags.hpp"
#include "SceneSupport.h"
#include "Grid.h"
#include "ObjPool.h"
#include "Publisher.h"

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
private:
	float gridCellWidth;
	float gridCellHeight;
	float gridLineThickness;
	int gridRows;
	int gridCols;

	float gridMinCellWidth;
	float gridMaxCellWidth;
	float gridMinCellHeight;
	float gridMaxCellHeight;
	float gridMinLineThickness;
	float gridMaxLineThickness;
	int gridMinRows;
	int gridMinCols;
	int gridMaxRows;
	int gridMaxCols;

	Grid<float> grid;

	bool simStarted;
	bool showLines;
	bool isDay;
	float dayNightBT;
	float gameSpd;
	float spawningStartTime;
	float spawningEndTime;
	int teamRegionsCase;
	int alphaTeamLocalXStart;
	int alphaTeamLocalXEnd;
	int alphaTeamLocalYStart;
	int alphaTeamLocalYEnd;
	int omegaTeamLocalXStart;
	int omegaTeamLocalXEnd;
	int omegaTeamLocalYStart;
	int omegaTeamLocalYEnd;
	int alphaTeamEntityCount;
	int omegaTeamEntityCount;
	int alphaTeamSpawnLimit;
	int omegaTeamSpawnLimit;
	ObjPool<Entity>* objPool;
	Publisher* publisher;

	///Shared SMs
	SM* skeleSM;
	SM* reptileSM;
	SM* boySM;
	SM* orcSM;

	struct CreateEntityParams final{
		CreateEntityParams() = default;
		~CreateEntityParams() = default;

		Vector3 im_LocalPos = Vector3();
	};

	Entity* CreateSkele(const CreateEntityParams& params) const; //Very high dmg, very low health, moderate range, moderate spd
	Entity* CreateReptile(const CreateEntityParams& params) const; //Very low dmg, very high health, high range, high spd
	Entity* CreateBoy(const CreateEntityParams& params) const; //Moderate dmg, moderate health, moderate range, moderate spd
	Entity* CreateOrc(const CreateEntityParams& params) const; //High dmg, high health, low range, low spd

	void SpawnEntity(const Obj::EntityType type, const ListenerFlags& teamFlag);

	void UpdateGridAttribs();
	void UpdateGridBlockData();
	void UpdateStates();
	void UpdateSkeleStates();
	void UpdateReptileStates();
	void UpdateBoyStates();
	void UpdateOrcStates();
	void UpdateGridEntityData();
	void UpdateEntities(const double dt);

	void RenderGrid();
	void RenderMystery();
	void RenderGridBlockData();
	void RenderEntities();
	void RenderEntitiesPart2(const Entity* const entity);
	void RenderRegions();
	void RenderTranslucentBlock();
	void RenderBG();

	void RenderSceneText();
	void RenderDebugInfoText(Mesh* const textMesh, const Color& textColor, const float textSize);
	void RenderControlsText(Mesh* const textMesh, const Color& textColor, const float textSize);
	void RenderGridAttribsText(Mesh* const textMesh, const Color& textColor, const float textSize);
	void RenderGameInfoText(Mesh* const textMesh, const Color& textColor, const float textSize);
};