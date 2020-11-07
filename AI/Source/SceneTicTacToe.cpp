#include "SceneTicTacToe.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

void SceneTicTacToe::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;
	m_noGrid = 3;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;

	m_bCrossTurn = rand() & 1;
	m_bGameOver = false;
	m_winner = WHO_CONTENT::WHO_NONE;

	for(int i = 0; i < 9; ++i){
		m_grid[i] = WHO_NONE;
	}
}

GameObject* SceneTicTacToe::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->active = true;
			++m_objectCount;
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_CROSS);
		m_goList.push_back(go);
	}
	return FetchGO();
}

int SceneTicTacToe::GetAIDecision()
{
	++m_objectCount;
	m_bCrossTurn = true;

	///Win if possible
	for(int i = 0; i < 3; ++i){
		if(m_grid[i] + m_grid[3 + i] + m_grid[6 + i] == WHO_CIRCLE * 2){
			if(m_grid[i] == WHO_NONE){
				return i;
			} else if(m_grid[3 + i] == WHO_NONE){
				return 3 + i;
			} else{
				return 6 + i;
			}
		}
	}
	for(int j = 0; j < 3; ++j){
		if(m_grid[j * 3] + m_grid[j * 3 + 1] + m_grid[j * 3 + 2] == WHO_CIRCLE * 2){
			if(m_grid[j * 3] == WHO_NONE){
				return j * 3;
			} else if(m_grid[j * 3 + 1] == WHO_NONE){
				return j * 3 + 1;
			} else{
				return j * 3 + 2;
			}
		}
	}
	if(m_grid[0] + m_grid[4] + m_grid[8] == WHO_CIRCLE * 2){
		if(m_grid[0] == WHO_NONE){
			return 0;
		} else if(m_grid[4] == WHO_NONE){
			return 4;
		} else{
			return 8;
		}
	}
	if(m_grid[2] + m_grid[4] + m_grid[6] == WHO_CIRCLE * 2){
		if(m_grid[2] == WHO_NONE){
			return 2;
		} else if(m_grid[4] == WHO_NONE){
			return 4;
		} else{
			return 6;
		}
	}

	///Block if possible
	for(int i = 0; i < 3; ++i){
		if(m_grid[i] + m_grid[3 + i] + m_grid[6 + i] == WHO_CROSS * 2){
			if(m_grid[i] == WHO_NONE){
				return i;
			} else if(m_grid[3 + i] == WHO_NONE){
				return 3 + i;
			} else{
				return 6 + i;
			}
		}
	}
	for(int j = 0; j < 3; ++j){
		if(m_grid[j * 3] + m_grid[j * 3 + 1] + m_grid[j * 3 + 2] == WHO_CROSS * 2){
			if(m_grid[j * 3] == WHO_NONE){
				return j * 3;
			} else if(m_grid[j * 3 + 1] == WHO_NONE){
				return j * 3 + 1;
			} else{
				return j * 3 + 2;
			}
		}
	}
	if(m_grid[0] + m_grid[4] + m_grid[8] == WHO_CROSS * 2){
		if(m_grid[0] == WHO_NONE){
			return 0;
		} else if(m_grid[4] == WHO_NONE){
			return 4;
		} else{
			return 8;
		}
	}
	if(m_grid[2] + m_grid[4] + m_grid[6] == WHO_CROSS * 2){
		if(m_grid[2] == WHO_NONE){
			return 2;
		} else if(m_grid[4] == WHO_NONE){
			return 4;
		} else{
			return 6;
		}
	}

	///Pick a random spot to place
	std::vector<int> indices;
	for(int i = 0; i < 9; ++i){
		if(m_grid[i] == WHO_NONE){
			indices.emplace_back(i);
		}
	}
	return indices[rand() % indices.size()];
}

void SceneTicTacToe::GameLogic(){
	for(int i = 0; i < 3; ++i){
		if(m_grid[i] != WHO_NONE && m_grid[i] == m_grid[3 + i] && m_grid[3 + i] == m_grid[6 + i] && m_grid[i] == m_grid[6 + i]){
			m_winner = m_grid[i];
			m_bGameOver = true;
			return;
		}
	}
	for(int j = 0; j < 3; ++j){
		if(m_grid[j * 3] != WHO_NONE && m_grid[j * 3] == m_grid[j * 3 + 1] && m_grid[j * 3 + 1] == m_grid[j * 3 + 2] && m_grid[j * 3] == m_grid[j * 3 + 2]){
			m_winner = m_grid[j * 3];
			m_bGameOver = true;
			return;
		}
	}
	if(m_grid[0] != WHO_NONE && m_grid[0] == m_grid[4] && m_grid[4] == m_grid[8] && m_grid[0] == m_grid[8]){
		m_winner = m_grid[0];
		m_bGameOver = true;
		return;
	}
	if(m_grid[2] != WHO_NONE && m_grid[2] == m_grid[4] && m_grid[4] == m_grid[6] && m_grid[2] == m_grid[6]){
		m_winner = m_grid[2];
		m_bGameOver = true;
		return;
	}
	if(m_objectCount == 9){
		m_bGameOver = true;
	}
}

void SceneTicTacToe::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('R'))
	{
		for(int i = 0; i < 9; ++i){
			m_grid[i] = WHO_NONE;
		}
		m_objectCount = 0;
		m_bCrossTurn = true;
		m_speed = 1.f;
		m_winner = WHO_NONE;
		m_bGameOver = false;
	}

	//Input Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		if(!m_bGameOver && m_bCrossTurn && posX < m_worldHeight){
			const float gridCellSize = m_worldHeight / 3.f;
			const int gridX = (int)posX / (int)gridCellSize;
			const int gridY = (int)posY / (int)gridCellSize;

			if(m_grid[gridY * 3 + gridX] == WHO_NONE)
			{
				m_grid[gridY * 3 + gridX] = WHO_CROSS;
				m_bCrossTurn = false;
				++m_objectCount;
			}
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
	static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	///Game Logic
	if(!m_bGameOver){
		if(!m_bCrossTurn && m_objectCount < 9){
			m_grid[GetAIDecision()] = WHO_CIRCLE;
		}
		GameLogic();
	}
}

void SceneTicTacToe::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_CROSS:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CROSS], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_CIRCLE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CIRCLE], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneTicTacToe::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_TICTACTOE], false);
	modelStack.PopMatrix();

	///Render symbols
	for(int i = 0; i < 9; ++i){
		const float gridCellSize = m_worldHeight / 3.f;
		const int gridX = (int)i % 3;
		const int gridY = (int)i / 3;

		modelStack.PushMatrix();
		modelStack.Translate((float)gridX * gridCellSize, (float)gridY * gridCellSize, 0.f);
		modelStack.Translate(m_worldHeight * 0.5f - gridCellSize, m_worldHeight * 0.5f - gridCellSize, 0.f);
		modelStack.Scale(gridCellSize, gridCellSize, 1.f);
		switch(m_grid[i]){
			case WHO_CROSS:
				RenderMesh(meshList[GEO_CROSS], false);
				break;
			case WHO_CIRCLE:
				RenderMesh(meshList[GEO_CIRCLE], false);
				break;
		}
		modelStack.PopMatrix();
	}

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	///On screen text
	static std::string winnerText[] = {"Draw", "Cross wins", "Circle wins"};

	std::ostringstream ss;
	ss.precision(3);
	ss << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	ss.str("");
	ss << "Count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	ss.str("");
	ss << "Turn: " << (m_bCrossTurn ? "Cross" : "Circle");
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 12);

	if(m_bGameOver)
	{
		ss.str("");
		ss << winnerText[m_winner == WHO_CIRCLE ? 2 : int(m_winner == WHO_CROSS)];
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 15);
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Tic Tac Toe (R to reset)", Color(0, 1, 0), 3, 50, 0);
}

void SceneTicTacToe::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if (m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}