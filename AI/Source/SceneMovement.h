#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include "GameObject.h"
#include "StateMachine.h"
#include <vector>
#include "SceneBase.h"

#pragma warning(push)
#pragma warning(disable: 26812)

class SceneMovement : public SceneBase
{
public:
	SceneMovement() = default;
	~SceneMovement() = default;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);
protected:
	std::vector<GameObject *> im_goList;
	float im_speed;
	float im_worldWidth;
	float im_worldHeight;
	GameObject *im_ghost;
	int im_objectCount;
	int im_noGrid;
	float im_gridSize;
	float im_gridOffset;
	float im_hourOfTheDay;

	int im_FishCount;

	StateMachine* fishSM;
	StateMachine* sharkSM;

	///Stats
	int im_DiedByHunger;
	int im_EatenByShark;
	int im_Overeat;

	void ChooseRandDir(GameObject* go);
	void Move(GameObject* go, Vector3& dir, double dt);
};

#endif