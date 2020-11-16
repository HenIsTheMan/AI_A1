#include <map>

#include "Scene.h"
#include "GL\glew.h"
#include "App.h"
#include "SpriteAni.h"

#include "StateAttack.h"
#include "StateDead.h"
#include "StateHeal.h"
#include "StateIdle.h"
#include "StateImmune.h"
#include "StateMultiply.h"
#include "StateRevive.h"

extern int winWidth;
extern int winHeight;

Scene::Scene():
	gridCellWidth(40.0f),
	gridCellHeight(40.0f),
	gridLineThickness(3.0f),
	gridRows(20),
	gridCols(20),
	gridMinRows(1),
	gridMinCols(1),
	gridMaxRows(30),
	gridMaxCols(30),
	grid(Grid<float>(0.0f, 0.0f, 0.0f, 0, 0)),
	isDay(false),
	dayNightBT(0.0f),
	objPool(new ObjPool<Entity>()),
	skeleSM(new SM()),
	reptileSM(new SM()),
	boySM(new SM()),
	orcSM(new SM())
{
	Math::InitRNG();

	objPool->CreateObjs(10000);

	skeleSM->AddState(StateID::StateIdle, new State(StateIdle::Enter, StateIdle::Update, StateIdle::Exit));
	skeleSM->AddState(StateID::StateAttack, new State(StateAttack::Enter, StateAttack::Update, StateAttack::Exit));
	skeleSM->AddState(StateID::StateDead, new State(StateDead::Enter, StateDead::Update, StateDead::Exit));
}

Scene::~Scene(){
	if(objPool){
		delete objPool;
		objPool = nullptr;
	}

	if(skeleSM){
		delete skeleSM;
		skeleSM = nullptr;
	}
	if(reptileSM){
		delete reptileSM;
		reptileSM = nullptr;
	}
	if(boySM){
		delete boySM;
		boySM = nullptr;
	}
	if(orcSM){
		delete orcSM;
		orcSM = nullptr;
	}
}

void Scene::Update(double dt){
	SceneSupport::Update(dt);

	if(dayNightBT <= elapsedTime){
		isDay = !isDay;
		dayNightBT = elapsedTime + 7.0f;
	}

	UpdateGridProperties();
	UpdateGridData();
	UpdateEntities();
}

void Scene::Render(){
	SceneSupport::Render();

	modelStack.PushMatrix();
	modelStack.Translate(
		-(float)winWidth * 0.5f,
		-(float)winHeight * 0.5f,
		0.0f
	);

	RenderGrid();
	RenderGridBG();
	RenderGridData();
	RenderEntities();
	RenderTranslucentBlock();
	RenderBG();
	RenderSceneText();

	modelStack.PopMatrix();
}

void Scene::UpdateGridProperties(){
	static bool isKeyDown1 = false;
	static bool isKeyDown2 = false;
	static bool isKeyDown3 = false;
	static bool isKeyDown4 = false;
	static bool isKeyDown5 = false;
	static bool isKeyDown6 = false;
	static bool isKeyDown7 = false;
	static bool isKeyDown8 = false;
	static bool isKeyDown9 = false;
	static bool isKeyDown0 = false;
	if(!isKeyDown1 && App::Key('1')){
		++gridCellWidth;
		isKeyDown1 = true;
	} else if(isKeyDown1 && !App::Key('1')){
		isKeyDown1 = false;
	}
	if(!isKeyDown2 && App::Key('2')){
		--gridCellWidth;
		isKeyDown2 = true;
	} else if(isKeyDown2 && !App::Key('2')){
		isKeyDown2 = false;
	}
	if(!isKeyDown3 && App::Key('3')){
		++gridCellHeight;
		isKeyDown3 = true;
	} else if(isKeyDown3 && !App::Key('3')){
		isKeyDown3 = false;
	}
	if(!isKeyDown4 && App::Key('4')){
		--gridCellHeight;
		isKeyDown4 = true;
	} else if(isKeyDown4 && !App::Key('4')){
		isKeyDown4 = false;
	}
	if(!isKeyDown5 && App::Key('5')){
		++gridLineThickness;
		isKeyDown5 = true;
	} else if(isKeyDown5 && !App::Key('5')){
		isKeyDown5 = false;
	}
	if(!isKeyDown6 && App::Key('6')){
		--gridLineThickness;
		isKeyDown6 = true;
	} else if(isKeyDown6 && !App::Key('6')){
		isKeyDown6 = false;
	}
	if(!isKeyDown7 && App::Key('7')){
		if(gridRows < gridMaxRows){
			++gridRows;
		}
		isKeyDown7 = true;
	} else if(isKeyDown7 && !App::Key('7')){
		isKeyDown7 = false;
	}
	if(!isKeyDown8 && App::Key('8')){
		if(gridRows > gridMinRows){
			--gridRows;

			///??
			std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
			const size_t& entityPoolSize = entityPool.size();

			for(size_t i = 0; i < entityPoolSize; ++i){
				std::pair<bool, Entity*>& element = entityPool[i];

				if(element.first){
					if(element.second->GetLocalPos().y >= gridRows){
						element.first = false;
					}
				}
			}
		}
		isKeyDown8 = true;
	} else if(isKeyDown8 && !App::Key('8')){
		isKeyDown8 = false;
	}
	if(!isKeyDown9 && App::Key('9')){
		if(gridCols < gridMaxCols){
			++gridCols;
		}
		isKeyDown9 = true;
	} else if(isKeyDown9 && !App::Key('9')){
		isKeyDown9 = false;
	}
	if(!isKeyDown0 && App::Key('0')){
		if(gridCols > gridMinCols){
			--gridCols;

			///??
			std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
			const size_t& entityPoolSize = entityPool.size();

			for(size_t i = 0; i < entityPoolSize; ++i){
				std::pair<bool, Entity*>& element = entityPool[i];

				if(element.first){
					if(element.second->GetLocalPos().x >= gridCols){
						element.first = false;
					}
				}
			}
		}
		isKeyDown0 = true;
	} else if(isKeyDown0 && !App::Key('0')){
		isKeyDown0 = false;
	}

	grid.SetCellWidth(gridCellWidth);
	grid.SetCellHeight(gridCellHeight);
	grid.SetLineThickness(gridLineThickness);
	grid.SetRows(gridRows);
	grid.SetCols(gridCols);
}

void Scene::UpdateGridData(){
	static bool isLMB = false;
	if(!isLMB && App::IsMousePressed(0)){
		isLMB = true;
	} else if(isLMB && !App::IsMousePressed(0)){
		isLMB = false;
	}

	static bool isRMB = false;
	if(!isRMB && App::IsMousePressed(1)){
		isRMB = true;
	} else if(isRMB && !App::IsMousePressed(1)){
		isRMB = false;
	}

	double mouseX;
	double mouseY;
	App::GetCursorPos(&mouseX, &mouseY);

	const float horizSize = (float)winWidth * (float)orthoProjectionScaleFactor;
	const float vertSize = (float)winHeight * (float)orthoProjectionScaleFactor;
	const float leftVal = ((float)winWidth - horizSize) * 0.5f;
	const float rightVal = leftVal + horizSize;
	const float bottomVal = ((float)winHeight - vertSize) * 0.5f;
	const float topVal = bottomVal + vertSize;

	const float trueMouseX = (float)mouseX * ((rightVal - leftVal) / (float)winWidth) + leftVal + im_Cam.pos.x;
	const float trueMouseY = (float)mouseY * ((topVal - bottomVal) / (float)winHeight) + bottomVal - im_Cam.pos.y;

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f;
	const float unitX = gridCellWidth + gridLineThickness;
	const float unitY = gridCellHeight + gridLineThickness;

	const float mouseRow = std::floor(((float)winHeight - trueMouseY - yOffset - gridLineThickness * 0.5f) / unitY);
	const float mouseCol = std::floor((trueMouseX - xOffset - gridLineThickness * 0.5f) / unitX);
	const float xTranslate = mouseCol * unitX
		+ xOffset
		+ gridCellWidth * 0.5f
		+ gridLineThickness;
	const float yTranslate = mouseRow * unitY
		+ yOffset
		+ gridCellHeight * 0.5f
		+ gridLineThickness;

	if(trueMouseX > xOffset + gridLineThickness * 0.5f && trueMouseX < xOffset + gridWidth - gridLineThickness * 0.5f
		&& trueMouseY > yOffset + gridLineThickness * 0.5f && trueMouseY < yOffset + gridHeight - gridLineThickness * 0.5f){
		if(isLMB){
			grid.SetData(true, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
		} else if(isRMB){
			grid.SetData(false, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
		}
	}
}

void Scene::UpdateEntities(){
	static int control = 0;

	if(control != 1){
		Entity* orc = CreateOrc();
		++control;
	}

	std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
	const size_t& entityPoolSize = entityPool.size();

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			const Entity* const& entity = entityPool[i].second;
		}
	}
}

void Scene::RenderGrid(){
	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f + gridLineThickness * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f + gridLineThickness * 0.5f;

	const int amtOfVertLines = grid.CalcAmtOfVertLines();
	for(int i = 0; i < amtOfVertLines; ++i){
		modelStack.PushMatrix();
		modelStack.Translate(
			xOffset + (gridCellWidth + gridLineThickness) * (float)i,
			(float)winHeight * 0.5f,
			0.0f
		);
		modelStack.Scale(
			gridLineThickness,
			gridHeight,
			1.0f
		);
		RenderMesh(meshList[(int)GeoType::GridLine], false);
		modelStack.PopMatrix();
	}

	const int amtOfHorizLines = grid.CalcAmtOfHorizLines();
	for(int i = 0; i < amtOfHorizLines; ++i){
		modelStack.PushMatrix();
		modelStack.Translate(
			(float)winWidth * 0.5f,
			yOffset + (gridCellHeight + gridLineThickness) * (float)i,
			0.0f
		);
		modelStack.Scale(
			gridWidth,
			gridLineThickness,
			1.0f
		);
		RenderMesh(meshList[(int)GeoType::GridLine], false);
		modelStack.PopMatrix();
	}
}

void Scene::RenderGridBG(){
	modelStack.PushMatrix();
	modelStack.Translate(
		(float)winWidth * 0.5f,
		(float)winHeight * 0.5f,
		0.0f
	);
	modelStack.Scale(
		grid.CalcWidth(),
		grid.CalcHeight(),
		1.0f
	);
	RenderMesh(meshList[(int)GeoType::GridBG], false);
	modelStack.PopMatrix();
}

void Scene::RenderGridData(){
	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f + gridLineThickness + gridCellWidth * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f + gridLineThickness + gridCellHeight * 0.5f;

	const std::vector<std::vector<bool>>& gridData = grid.GetData();

	for(int i = 0; i < gridRows; ++i){
		for(int j = 0; j < gridCols; ++j){
			if(gridData[i][j]){
				modelStack.PushMatrix();
				modelStack.Translate(
					xOffset + (gridLineThickness + gridCellWidth) * (float)j,
					yOffset + (gridLineThickness + gridCellHeight) * (float)i,
					0.1f
				);
				modelStack.Scale(
					gridCellWidth,
					gridCellHeight,
					1.0f
				);
				RenderMesh(meshList[(int)GeoType::Block], false);
				modelStack.PopMatrix();
			}
		}
	}
}

void Scene::RenderEntities(){
	const std::vector<std::pair<bool, Entity*>>& entityPool = objPool->GetPool();
	const size_t& entityPoolSize = entityPool.size();

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xPosOffset = ((float)winWidth - gridWidth) * 0.5f + gridCellWidth * 0.5f + gridLineThickness;
	const float yPosOffset = ((float)winHeight - gridHeight) * 0.5f + gridCellHeight * 0.5f + gridLineThickness;

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			const Entity* const& entity = entityPool[i].second;

			const Vector3& entityLocalPos = entity->GetLocalPos();
			const Vector3& entityLocalScale = entity->GetLocalScale();

			const Vector3& entityWorldPos = Vector3(
				xPosOffset + entityLocalPos.x * (gridCellWidth + gridLineThickness),
				yPosOffset + entityLocalPos.y * (gridCellHeight + gridLineThickness),
				0.1f
			);
			const Vector3& entityWorldScale = Vector3(
				entityLocalScale.x * gridCellWidth,
				entityLocalScale.y * gridCellHeight,
				1.0f
			);

			modelStack.PushMatrix();

			modelStack.Translate(
				entityWorldPos.x,
				entityWorldPos.y,
				entityWorldPos.z
			);

			modelStack.Scale(
				entityWorldScale.x,
				entityWorldScale.y,
				entityWorldScale.z
			);

			ManualRenderMesh("OrcMoveDown", elapsedTime, 0.1f, meshList[(int)GeoType::Orc], false);

			modelStack.PopMatrix();
		}
	}
}

void Scene::RenderTranslucentBlock(){
	double mouseX;
	double mouseY;
	App::GetCursorPos(&mouseX, &mouseY);

	const float horizSize = (float)winWidth * (float)orthoProjectionScaleFactor;
	const float vertSize = (float)winHeight * (float)orthoProjectionScaleFactor;
	const float leftVal = ((float)winWidth - horizSize) * 0.5f;
	const float rightVal = leftVal + horizSize;
	const float bottomVal = ((float)winHeight - vertSize) * 0.5f;
	const float topVal = bottomVal + vertSize;

	const float trueMouseX = (float)mouseX * ((rightVal - leftVal) / (float)winWidth) + leftVal + im_Cam.pos.x;
	const float trueMouseY = (float)mouseY * ((topVal - bottomVal) / (float)winHeight) + bottomVal - im_Cam.pos.y;

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f;

	if(trueMouseX > xOffset + gridLineThickness * 0.5f && trueMouseX < xOffset + gridWidth - gridLineThickness * 0.5f
		&& trueMouseY > yOffset + gridLineThickness * 0.5f && trueMouseY < yOffset + gridHeight - gridLineThickness * 0.5f){
		const float unitX = gridCellWidth + gridLineThickness;
		const float unitY = gridCellHeight + gridLineThickness;

		const float mouseRow = std::floor(((float)winHeight - trueMouseY - yOffset - gridLineThickness * 0.5f) / unitY);
		const float mouseCol = std::floor((trueMouseX - xOffset - gridLineThickness * 0.5f) / unitX);
		const float xTranslate = mouseCol * unitX
			+ xOffset
			+ gridCellWidth * 0.5f
			+ gridLineThickness;
		const float yTranslate = mouseRow * unitY
			+ yOffset
			+ gridCellHeight * 0.5f
			+ gridLineThickness;

		modelStack.PushMatrix();
			modelStack.Translate(
				xTranslate,
				yTranslate,
				0.1f
			);
			modelStack.Scale(
				gridCellWidth,
				gridCellHeight,
				1.0f
			);
			RenderMesh(meshList[(int)GeoType::Block], true, Color(), 0.5f);
		modelStack.PopMatrix();
	}
}

void Scene::RenderBG(){
	modelStack.PushMatrix();
		modelStack.Translate(
			im_Cam.pos.x + (float)winWidth * 0.5f,
			im_Cam.pos.y + (float)winHeight * 0.5f,
			0.0f
		);
		modelStack.Scale(
			(float)winWidth,
			(float)winHeight,
			1.0f
		);
		if(isDay){
			RenderMesh(meshList[(int)GeoType::DayBG], false);
		} else{
			RenderMesh(meshList[(int)GeoType::NightBG], false);
		}
	modelStack.PopMatrix();
}

void Scene::RenderSceneText(){
	static Mesh* textMesh = meshList[(int)GeoType::Text];
	static Color textColor = Color();
	static float textSize = 0.0f;
	textSize = winHeight * 0.05f;

	///Debug info
	RenderTextOnScreen(
		textMesh,
		"Elapsed time: " + std::to_string(elapsedTime).substr(0, std::to_string((int)elapsedTime).length() + 3),
		textColor,
		textSize,
		0.0f,
		textSize * 0.0f
	);
	RenderTextOnScreen(
		textMesh,
		"FPS: " + std::to_string(FPS).substr(0, std::to_string((int)FPS).length() + 3),
		textColor,
		textSize,
		0.0f,
		textSize * 1.0f
	);
	//RenderTextOnScreen(
	//	textMesh,
	//	"Obj count: " + std::to_string(im_objectCount),
	//	textColor,
	//	textSize,
	//	0.0f,
	//	textSize * 1.0f
	//);

	///Controls
	RenderTextOnScreen(
		textMesh,
		"Tab: ...",
		textColor,
		textSize,
		0.0f,
		textSize * 2.0f
	);
	RenderTextOnScreen(
		textMesh,
		"F1: Toggle fullscreen",
		textColor,
		textSize,
		0.0f,
		textSize * 3.0f
	);
	RenderTextOnScreen(
		textMesh,
		"F2: Change polygon mode",
		textColor,
		textSize,
		0.0f,
		textSize * 4.0f
	);
	RenderTextOnScreen(
		textMesh,
		"WASD: Move cam",
		textColor,
		textSize,
		0.0f,
		textSize * 5.0f
	);
	//RenderTextOnScreen(
	//	textMesh,
	//	"Game Spd: " + std::to_string(im_speed).substr(0, std::to_string((int)im_speed).length() + 2),
	//	textColor,
	//	textSize,
	//	0.0f,
	//	textSize * 5.0f
	//);

	///Others
	//RenderTextOnScreen(
	//	textMesh,
	//	"DiedByHunger count: " + std::to_string(im_DiedByHunger),
	//	textColor,
	//	textSize,
	//	(float)winWidth,
	//	textSize * 0.0f,
	//	TextAlignment::Right
	//);
}

Entity* Scene::CreateSkele() const{
}

Entity* Scene::CreateReptile() const{
}

Entity* Scene::CreateBoy() const{
}

Entity* Scene::CreateOrc() const{
	Entity* entity = objPool->RetrieveInactiveObj();

	entity->SetType(Obj::EntityType::Orc);
	entity->SetLocalPos(2.0f, 1.0f, 0.0f);
	entity->SetLocalScale(1.0f, 1.0f, 1.0f);

	entity->SetDir(1.0f, 0.0f, 0.0f);
	entity->SetSpd(50.0f);
	entity->SetStepsLeft(0);

	entity->SetDmg(10.0f);
	entity->SetRange(1.0f);
	entity->SetHealth(100.0f);
	entity->SetTimeLeft(0.0f);
	entity->SetTarget(nullptr);

	entity->SetStateMachine(orcSM);
	entity->SetCurrState();
	entity->SetNextState(const State* const nextState);
}