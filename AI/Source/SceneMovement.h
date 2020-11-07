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
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	int m_objectCount;
	int m_noGrid;
	float m_gridSize;
	float m_gridOffset;
	float m_hourOfTheDay;

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