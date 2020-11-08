#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include <vector>

#include "GameObject.h"
#include "StateMachine.h"
#include "SceneBase.h"
#include "Grid.h"

#pragma warning(push)
#pragma warning(disable: 26812)

class SceneMovement final: public SceneBase{
public:
	SceneMovement();
	~SceneMovement();

	void Update(double dt) override;
	void Render() override;

	void RenderGO(GameObject *go);

	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);
protected:
	std::vector<GameObject*> im_goList;
	float im_speed;
	int im_objectCount;
	int im_noGrid;
	float im_gridSize;
	float im_gridOffset;
	float im_hourOfTheDay;

	///Stats
	int im_FishCount;
	int im_DiedByHunger;
	int im_EatenByShark;
	int im_Overeat;

	StateMachine* fishSM;
	StateMachine* sharkSM;

	float gridCellWidth;
	float gridCellHeight;
	float gridLineThickness;
	int gridRows;
	int gridCols;
	Grid<float> grid;

	void ChooseRandDir(GameObject* go);
	void Move(GameObject* go, Vector3& dir, double dt);

	void UpdateGrid();

	void RenderGrid();
	void RenderGridBG();
	void RenderSceneText();
};

#endif