#ifndef SCENE_TICTACTOE_H
#define SCENE_TICTACTOE_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

#pragma warning(push)
#pragma warning(disable: 26812)

class SceneTicTacToe : public SceneBase
{
	enum WHO_CONTENT
	{
		WHO_NONE,
		WHO_CROSS = -8,
		WHO_CIRCLE = 23,
	};
public:
	SceneTicTacToe() = default;
	~SceneTicTacToe() = default;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	GameObject* FetchGO();

	int GetAIDecision();
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
	WHO_CONTENT m_grid[9];
	bool m_bCrossTurn;
	bool m_bGameOver;
	WHO_CONTENT m_winner;

	void GameLogic();
};

#endif