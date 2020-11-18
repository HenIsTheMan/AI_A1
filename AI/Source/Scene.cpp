#include "Scene.h"
#include "GL\glew.h"
#include "App.h"
#include "SpriteAni.h"

#include "StateSkeleIdle.h"
#include "StateSkeleAttack.h"
#include "StateSkeleDead.h"
#include "StateSkeleRevive.h"

#include "StateReptileIdle.h"
#include "StateReptileAttack.h"
#include "StateReptileDead.h"
#include "StateReptileMultiply.h"

#include "StateBoyIdle.h"
#include "StateBoyAttack.h"
#include "StateBoyDead.h"
#include "StateBoyHeal.h"

#include "StateOrcIdle.h"
#include "StateOrcAttack.h"
#include "StateOrcDead.h"
#include "StateOrcImmune.h"

extern int winWidth;
extern int winHeight;

Scene::Scene():
	gridCellWidth(40.0f),
	gridCellHeight(40.0f),
	gridLineThickness(2.5f),
	gridRows(20),
	gridCols(20),
	gridMinCellWidth(20.0f),
	gridMaxCellWidth(60.0f),
	gridMinCellHeight(20.0f),
	gridMaxCellHeight(60.0f),
	gridMinLineThickness(0.5f),
	gridMaxLineThickness(4.0f),
	gridMinRows(0),
	gridMinCols(0),
	gridMaxRows(30),
	gridMaxCols(30),
	grid(Grid<float>(0.0f, 0.0f, 0.0f, 0, 0)),
	isDay(false),
	dayNightBT(0.0f),
	gameSpd(1.0f),
	objPool(new ObjPool<Entity>()),
	publisher(Publisher::RetrieveGlobalObjPtr()),
	skeleSM(new SM()),
	reptileSM(new SM()),
	boySM(new SM()),
	orcSM(new SM())
{
	Math::InitRNG();

	objPool->CreateObjs(10000);

	skeleSM->AddState(new State(StateID::StateSkeleIdle, StateSkeleIdle::Enter, StateSkeleIdle::Update, StateSkeleIdle::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleAttack, StateSkeleAttack::Enter, StateSkeleAttack::Update, StateSkeleAttack::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleDead, StateSkeleDead::Enter, StateSkeleDead::Update, StateSkeleDead::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleRevive, StateSkeleRevive::Enter, StateSkeleRevive::Update, StateSkeleRevive::Exit));

	reptileSM->AddState(new State(StateID::StateReptileIdle, StateReptileIdle::Enter, StateReptileIdle::Update, StateReptileIdle::Exit));
	reptileSM->AddState(new State(StateID::StateReptileAttack, StateReptileAttack::Enter, StateReptileAttack::Update, StateReptileAttack::Exit));
	reptileSM->AddState(new State(StateID::StateReptileDead, StateReptileDead::Enter, StateReptileDead::Update, StateReptileDead::Exit));
	reptileSM->AddState(new State(StateID::StateReptileMultiply, StateReptileMultiply::Enter, StateReptileMultiply::Update, StateReptileMultiply::Exit));

	boySM->AddState(new State(StateID::StateBoyIdle, StateBoyIdle::Enter, StateBoyIdle::Update, StateBoyIdle::Exit));
	boySM->AddState(new State(StateID::StateBoyAttack, StateBoyAttack::Enter, StateBoyAttack::Update, StateBoyAttack::Exit));
	boySM->AddState(new State(StateID::StateBoyDead, StateBoyDead::Enter, StateBoyDead::Update, StateBoyDead::Exit));
	boySM->AddState(new State(StateID::StateBoyHeal, StateBoyHeal::Enter, StateBoyHeal::Update, StateBoyHeal::Exit));

	orcSM->AddState(new State(StateID::StateOrcIdle, StateOrcIdle::Enter, StateOrcIdle::Update, StateOrcIdle::Exit));
	orcSM->AddState(new State(StateID::StateOrcAttack, StateOrcAttack::Enter, StateOrcAttack::Update, StateOrcAttack::Exit));
	orcSM->AddState(new State(StateID::StateOrcDead, StateOrcDead::Enter, StateOrcDead::Update, StateOrcDead::Exit));
	orcSM->AddState(new State(StateID::StateOrcImmune, StateOrcImmune::Enter, StateOrcImmune::Update, StateOrcImmune::Exit));

	publisher->AddListener(ListenerID::ObjPool, ListenerCategory::ObjPool, objPool);
}

Scene::~Scene(){
	if(objPool){
		delete objPool;
		objPool = nullptr;
	}

	if(publisher){
		publisher->Destroy();
		publisher = nullptr;
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

	static bool isKeyDownZ = false;
	static bool isKeyDownX = false;
	if(!isKeyDownZ && App::Key('Z')){
		gameSpd += 0.1f;
		isKeyDownZ = true;
	} else if(isKeyDownZ && !App::Key('Z')){
		isKeyDownZ = false;
	}
	if(!isKeyDownX && App::Key('X')){
		gameSpd -= 0.1f;
		isKeyDownX = true;
	} else if(isKeyDownX && !App::Key('X')){
		isKeyDownX = false;
	}
	gameSpd = Math::Clamp(gameSpd, 0.2f, 4.0f);

	UpdateGridAttribs();
	UpdateGridData();

	///??
	std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
	const size_t& entityPoolSize = entityPool.size();

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			Entity* const entity = entityPool[i].second;

			const Vector3& entityLocalPos = entity->GetLocalPos();
			if(entityLocalPos.y >= (float)gridRows - 1.0f){
				if(!(int)gridRows){
					entityPool[i].first = false;
					continue;
				}
				entity->SetLocalPos(entityLocalPos.x, float(gridRows - 1), entityLocalPos.z);
			}
			if(entity->GetGridTargetLocalPos().y >= (float)gridRows - 1.0f){
				entity->SetGridTargetLocalPos(entityLocalPos.x, float(gridRows - 1), entityLocalPos.z);
				//entityPool[i].first = false;
			}

			if(entity->GetLocalPos().x >= (float)gridCols - 1.0f){
				if(!(int)gridCols){
					entityPool[i].first = false;
					continue;
				}
				entity->SetLocalPos(float(gridCols - 1), entityLocalPos.y, entityLocalPos.z);
			}
			if(entity->GetGridTargetLocalPos().x >= (float)gridCols - 1.0f){
				entity->SetGridTargetLocalPos(float(gridCols - 1), entityLocalPos.y, entityLocalPos.z);
				//entityPool[i].first = false;
			}
		}
	}

	UpdateStates();
	UpdateEntities(dt * gameSpd);
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
	RenderTranslucentBlock();
	RenderEntities();
	RenderBG();
	RenderSceneText();

	modelStack.PopMatrix();
}

Entity* Scene::CreateSkele(const CreateEntityParams& params) const{
	Entity* entity = objPool->RetrieveActivatedObj();

	entity->SetType(Obj::EntityType::Skele);
	entity->SetLocalPos(params.im_LocalPos);
	entity->SetLocalScale(1.0f, 1.0f, 1.0f);

	entity->SetDmg(22.0f);
	entity->SetRange(1.2f);
	entity->SetMaxHealth(45.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
	entity->SetSpd(1.4f);

	entity->SetTarget(nullptr);
	ChooseRandDir(entity, &grid, gridRows, gridCols);
	entity->SetTimeLeft(0.0f);

	entity->SetStateMachine(skeleSM);
	entity->SetCurrState(skeleSM->GetState(StateID::StateSkeleIdle));
	entity->SetNextState(skeleSM->GetState(StateID::StateSkeleIdle));
	entity->SetSpriteAniMiddleName("Static");

	return entity;
}

Entity* Scene::CreateReptile(const CreateEntityParams& params) const{
	Entity* entity = objPool->RetrieveActivatedObj();

	entity->SetType(Obj::EntityType::Reptile);
	entity->SetLocalPos(params.im_LocalPos);
	entity->SetLocalScale(1.0f, 1.0f, 1.0f);

	entity->SetDmg(3.0f);
	entity->SetRange(2.1f);
	entity->SetMaxHealth(240.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
	entity->SetSpd(1.8f);

	entity->SetTarget(nullptr);
	ChooseRandDir(entity, &grid, gridRows, gridCols);
	entity->SetTimeLeft(0.0f);

	entity->SetStateMachine(reptileSM);
	entity->SetCurrState(reptileSM->GetState(StateID::StateReptileIdle));
	entity->SetNextState(reptileSM->GetState(StateID::StateReptileIdle));
	entity->SetSpriteAniMiddleName("Static");

	return entity;
}

Entity* Scene::CreateBoy(const CreateEntityParams& params) const{
	Entity* entity = objPool->RetrieveActivatedObj();

	entity->SetType(Obj::EntityType::Boy);
	entity->SetLocalPos(params.im_LocalPos);
	entity->SetLocalScale(1.0f, 1.0f, 1.0f);

	entity->SetDmg(10.0f);
	entity->SetRange(1.3f);
	entity->SetMaxHealth(85.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
	entity->SetSpd(1.2f);

	entity->SetTarget(nullptr);
	ChooseRandDir(entity, &grid, gridRows, gridCols);
	entity->SetTimeLeft(0.0f);

	entity->SetStateMachine(boySM);
	entity->SetCurrState(boySM->GetState(StateID::StateBoyIdle));
	entity->SetNextState(boySM->GetState(StateID::StateBoyIdle));
	entity->SetSpriteAniMiddleName("Static");

	return entity;
}

Entity* Scene::CreateOrc(const CreateEntityParams& params) const{
	Entity* entity = objPool->RetrieveActivatedObj();

	entity->SetType(Obj::EntityType::Orc);
	entity->SetLocalPos(params.im_LocalPos);
	entity->SetLocalScale(1.0f, 1.0f, 1.0f);

	entity->SetDmg(15.0f);
	entity->SetRange(0.7f);
	entity->SetMaxHealth(150.0f);
	entity->SetCurrHealth(entity->GetMaxHealth());
	entity->SetSpd(0.8f);

	entity->SetTarget(nullptr);
	ChooseRandDir(entity, &grid, gridRows, gridCols);
	entity->SetTimeLeft(0.0f);

	entity->SetStateMachine(orcSM);
	entity->SetCurrState(orcSM->GetState(StateID::StateOrcIdle));
	entity->SetNextState(orcSM->GetState(StateID::StateOrcIdle));
	entity->SetSpriteAniMiddleName("Static");

	return entity;
}

void Scene::UpdateGridAttribs(){
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
		if(gridCellWidth < gridMaxCellWidth){
			++gridCellWidth;
		}
		isKeyDown1 = true;
	} else if(isKeyDown1 && !App::Key('1')){
		isKeyDown1 = false;
	}
	if(!isKeyDown2 && App::Key('2')){
		if(gridCellWidth > gridMinCellWidth){
			--gridCellWidth;
		}
		isKeyDown2 = true;
	} else if(isKeyDown2 && !App::Key('2')){
		isKeyDown2 = false;
	}
	if(!isKeyDown3 && App::Key('3')){
		if(gridCellHeight < gridMaxCellHeight){
			++gridCellHeight;
		}
		isKeyDown3 = true;
	} else if(isKeyDown3 && !App::Key('3')){
		isKeyDown3 = false;
	}
	if(!isKeyDown4 && App::Key('4')){
		if(gridCellHeight > gridMinCellHeight){
			--gridCellHeight;
		}
		isKeyDown4 = true;
	} else if(isKeyDown4 && !App::Key('4')){
		isKeyDown4 = false;
	}
	if(!isKeyDown5 && App::Key('5')){
		if(gridLineThickness < gridMaxLineThickness){
			gridLineThickness += 0.1f;
		}
		isKeyDown5 = true;
	} else if(isKeyDown5 && !App::Key('5')){
		isKeyDown5 = false;
	}
	if(!isKeyDown6 && App::Key('6')){
		if(gridLineThickness > gridMinLineThickness){
			gridLineThickness -= 0.1f;
		}
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

void Scene::UpdateStates(){
	UpdateSkeleStates();
	UpdateReptileStates();
	UpdateBoyStates();
	UpdateOrcStates();
}

void Scene::UpdateSkeleStates(){
	StateSkeleIdle* const stateSkeleIdle = ((StateSkeleIdle*)skeleSM->GetState(StateID::StateSkeleIdle));
	stateSkeleIdle->im_Grid = &grid;
	stateSkeleIdle->im_GridRows = gridRows;
	stateSkeleIdle->im_GridCols = gridCols;

	StateSkeleDead* const stateSkeleDead = ((StateSkeleDead*)skeleSM->GetState(StateID::StateSkeleDead));
	stateSkeleDead->im_ObjPool = objPool;
}

void Scene::UpdateReptileStates(){
	StateReptileIdle* const stateReptileIdle = ((StateReptileIdle*)reptileSM->GetState(StateID::StateReptileIdle));
	stateReptileIdle->im_Grid = &grid;
	stateReptileIdle->im_GridRows = gridRows;
	stateReptileIdle->im_GridCols = gridCols;

	static float updateCommonDirBT = 0.0f;
	if(updateCommonDirBT <= elapsedTime){
		ChooseRandPairOfPerpendicularDirs(stateReptileIdle->im_CommonDirs);
		updateCommonDirBT = elapsedTime + 1.0f;
	}

	StateReptileDead* const stateReptileDead = ((StateReptileDead*)reptileSM->GetState(StateID::StateReptileDead));
	stateReptileDead->im_ObjPool = objPool;
}

void Scene::UpdateBoyStates(){
	StateBoyIdle* const stateBoyIdle = ((StateBoyIdle*)boySM->GetState(StateID::StateBoyIdle));
	stateBoyIdle->im_Grid = &grid;
	stateBoyIdle->im_GridRows = gridRows;
	stateBoyIdle->im_GridCols = gridCols;

	StateBoyDead* const stateBoyDead = ((StateBoyDead*)boySM->GetState(StateID::StateBoyDead));
	stateBoyDead->im_ObjPool = objPool;
}

void Scene::UpdateOrcStates(){
	StateOrcIdle* const stateOrcIdle = ((StateOrcIdle*)orcSM->GetState(StateID::StateOrcIdle));
	stateOrcIdle->im_Grid = &grid;
	stateOrcIdle->im_GridRows = gridRows;
	stateOrcIdle->im_GridCols = gridCols;

	StateOrcDead* const stateOrcDead = ((StateOrcDead*)orcSM->GetState(StateID::StateOrcDead));
	stateOrcDead->im_ObjPool = objPool;
}

void Scene::UpdateEntities(const double dt){
	static int control = 0;

	if(control != 20){
		Entity* skele = CreateSkele({
			Vector3(5.0f, 15.0f, 0.0f)
		});
		Entity* reptile = CreateReptile({
			Vector3(15.0f, 12.0f, 0.0f)
		});
		Entity* boy = CreateBoy({
			Vector3(5.0f, 4.0f, 0.0f)
		});
		Entity* orc = CreateOrc({
			Vector3(18.5f, 3.0f, 0.0f)
		});

		orc->SetCurrHealth(0.0f);
		++control;
	}

	std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
	const size_t& entityPoolSize = entityPool.size();

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			Entity* const entity = entityPool[i].second;

			switch(entity->GetType()){
				using namespace Obj;

				case EntityType::Skele:
					skeleSM->CheckForStateTransition(entity);
					skeleSM->UpdateCurrState(entity, dt);
					break;
				case EntityType::Reptile:
					reptileSM->CheckForStateTransition(entity);
					reptileSM->UpdateCurrState(entity, dt);
					break;
				case EntityType::Boy:
					boySM->CheckForStateTransition(entity);
					boySM->UpdateCurrState(entity, dt);
					break;
				case EntityType::Orc:
					orcSM->CheckForStateTransition(entity);
					orcSM->UpdateCurrState(entity, dt);
					break;
			}
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

	static float individualDepthOffset = 0.0f;
	float opacity = 1.0f;

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			const Entity* const entity = entityPool[i].second;

			const Vector3& entityLocalPos = entity->GetLocalPos();
			const Vector3& entityLocalScale = entity->GetLocalScale();

			const Vector3& entityWorldPos = Vector3(
				xPosOffset + entityLocalPos.x * (gridCellWidth + gridLineThickness),
				yPosOffset + entityLocalPos.y * (gridCellHeight + gridLineThickness),
				0.2f + individualDepthOffset
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

			switch(entity->GetCurrState()->GetID()){
				case StateID::StateSkeleRevive:
					ManualRenderMesh("SkeleHibernate", 1.0f, 1.0f, meshList[(int)GeoType::Skele], true, Color(1.0f, 0.0f, 0.0f), 0.8f);
					break;
				case StateID::StateReptileMultiply:
					ManualRenderMesh("ReptileProcreate", 1.0f, 1.0f, meshList[(int)GeoType::Reptile], true, Color(1.0f, 1.0f, 0.0f), 0.8f);
					break;
				case StateID::StateBoyHeal:
					ManualRenderMesh("BoyHeal", 1.0f, 1.0f, meshList[(int)GeoType::Boy], true, Color(0.0f, 1.0f, 0.0f), 0.8f);
					break;
				case StateID::StateOrcImmune:
					ManualRenderMesh("OrcImmune", 1.0f, 1.0f, meshList[(int)GeoType::Orc], true, Color(0.0f, 0.0f, 1.0f), 0.8f);
					break;
				case StateID::StateSkeleDead:
					opacity = entity->GetTimeLeft() / 4.0f;
					ManualRenderMesh("SkeleFacePlant", 1.0f, 1.0f, meshList[(int)GeoType::Skele], true, Color(), opacity);
					break;
				case StateID::StateReptileDead:
					opacity = entity->GetTimeLeft() / 6.0f;
					ManualRenderMesh("ReptileFacePlant", 1.0f, 1.0f, meshList[(int)GeoType::Reptile], true, Color(), opacity);
					break;
				case StateID::StateBoyDead:
					opacity = entity->GetTimeLeft() / 5.0f;
					ManualRenderMesh("BoyFacePlant", 1.0f, 1.0f, meshList[(int)GeoType::Boy], true, Color(), opacity);
					break;
				case StateID::StateOrcDead:
					opacity = entity->GetTimeLeft() / 7.0f;
					ManualRenderMesh("OrcFacePlant", 1.0f, 1.0f, meshList[(int)GeoType::Orc], true, Color(), opacity);
					break;
				default:
					RenderEntitiesPart2(entity);
			}

			///Render health bar
			const float ratio = (float)entity->GetCurrHealth() / (float)entity->GetMaxHealth();

			modelStack.PushMatrix();

			modelStack.Translate(
				0.0f,
				0.4f,
				0.2f + individualDepthOffset
			);
			modelStack.Scale(
				0.9f,
				0.1f,
				1.0f
			);

			modelStack.PushMatrix();

			modelStack.Translate(
				-(1.f - ratio) * 0.5f,
				0.0f,
				0.0f
			);
			modelStack.Scale(
				ratio,
				1.0f,
				1.0f
			);

			RenderMesh(meshList[(int)GeoType::HealthBar], true, Color(0.0f, 1.0f, 0.0f), opacity);

			modelStack.PopMatrix();

			RenderMesh(meshList[(int)GeoType::HealthBar], true, Color(1.0f, 0.0f, 0.0f), opacity);

			modelStack.PopMatrix();

			modelStack.PopMatrix();

			individualDepthOffset += 0.01f;
		}
	}

	individualDepthOffset = 0.0f;
}

void Scene::RenderEntitiesPart2(const Entity* const entity){
	float spriteAniDelay = 0.0f;
	Mesh* spriteAniMesh = nullptr;
	std::string spriteAniName;

	switch(entity->GetType()){
		using namespace Obj;

		case EntityType::Skele:
			spriteAniMesh = meshList[(int)GeoType::Skele];
			spriteAniName += "Skele";
			break;
		case EntityType::Reptile:
			spriteAniMesh = meshList[(int)GeoType::Reptile];
			spriteAniName += "Reptile";
			break;
		case EntityType::Boy:
			spriteAniMesh = meshList[(int)GeoType::Boy];
			spriteAniName += "Boy";
			break;
		case EntityType::Orc:
			spriteAniMesh = meshList[(int)GeoType::Orc];
			spriteAniName += "Orc";
			break;
	}

	const std::string& entitySpriteAniMiddleName = entity->GetSpriteAniMiddleName();
	assert(entitySpriteAniMiddleName != "");

	spriteAniName += entitySpriteAniMiddleName;
	if(entitySpriteAniMiddleName == "Static"){
		spriteAniDelay = 1.0f;
	} else if(entitySpriteAniMiddleName == "Move"){
		spriteAniDelay = 0.1f;
	} else if(entitySpriteAniMiddleName == "Attack"){
		spriteAniDelay = 0.3f;
	}

	assert(spriteAniDelay != 0.0f);
	assert(spriteAniMesh != nullptr);
	assert(spriteAniName != "");

	const Vector3 vec = entity->GetGridTargetLocalPos() - entity->GetLocalPos();
	if(vec.x > 0.0f){
		spriteAniName += (std::string)"Right";
	} else if(vec.x < 0.0f){
		spriteAniName += (std::string)"Left";
	} else if(vec.y > 0.0f){
		spriteAniName += (std::string)"Up";
	} else if(vec.y < 0.0f){
		spriteAniName += (std::string)"Down";
	} else{
		spriteAniName += (std::string)"Right";
	}

	ManualRenderMesh(spriteAniName, elapsedTime, spriteAniDelay, spriteAniMesh, false);
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
	Mesh* const textMesh = meshList[(int)GeoType::Text];
	const float textSize = winHeight * 0.05f;

	RenderDebugInfoText(textMesh, Color(), textSize);
	RenderControlsText(textMesh, Color(1.0f, 0.0f, 1.0f), textSize);
	RenderGridAttribsText(textMesh, Color(1.0f, 1.0f, 0.0f), textSize);
}

void Scene::RenderDebugInfoText(Mesh* const textMesh, const Color& textColor, const float textSize){
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
	RenderTextOnScreen(
		textMesh,
		"Game Spd: " + std::to_string(gameSpd).substr(0, std::to_string((int)gameSpd).length() + 2),
		textColor,
		textSize,
		0.0f,
		textSize * 2.0f
	);
	RenderTextOnScreen(
		textMesh,
		"Inactive objs: " + std::to_string(objPool->GetPool().size()),
		textColor,
		textSize,
		0.0f,
		textSize * 3.0f
	);
	RenderTextOnScreen( //??
		textMesh,
		"Active objs: ",
		textColor,
		textSize,
		0.0f,
		textSize * 4.0f
	);
}

void Scene::RenderControlsText(Mesh* const textMesh, const Color& textColor, const float textSize){
	RenderTextOnScreen(
		textMesh,
		"F1: Toggle fullscreen",
		textColor,
		textSize,
		0.0f,
		textSize * 19.0f
	);
	RenderTextOnScreen(
		textMesh,
		"F2: Change polygon mode",
		textColor,
		textSize,
		0.0f,
		textSize * 18.0f
	);
	RenderTextOnScreen(
		textMesh,
		"Tab: ...",
		textColor,
		textSize,
		0.0f,
		textSize * 17.0f
	);
	RenderTextOnScreen(
		textMesh,
		"WASD: Move cam",
		textColor,
		textSize,
		0.0f,
		textSize * 16.0f
	);
	RenderTextOnScreen(
		textMesh,
		"R: Reset cam",
		textColor,
		textSize,
		0.0f,
		textSize * 15.0f
	);
	RenderTextOnScreen(
		textMesh,
		"Z: Increase game spd",
		textColor,
		textSize,
		0.0f,
		textSize * 14.0f
	);
	RenderTextOnScreen(
		textMesh,
		"X: Decrease game spd",
		textColor,
		textSize,
		0.0f,
		textSize * 13.0f
	);
}

void Scene::RenderGridAttribsText(Mesh* const textMesh, const Color& textColor, const float textSize){
	RenderTextOnScreen(
		textMesh,
		"Grid cell width: " + std::to_string(gridCellWidth).substr(0, std::to_string((int)gridCellWidth).length() + 2),
		textColor,
		textSize,
		(float)winWidth,
		textSize * 0.0f,
		TextAlignment::Right
	);
	RenderTextOnScreen(
		textMesh,
		"Grid cell height: " + std::to_string(gridCellHeight).substr(0, std::to_string((int)gridCellHeight).length() + 2),
		textColor,
		textSize,
		(float)winWidth,
		textSize * 1.0f,
		TextAlignment::Right
	);
	RenderTextOnScreen(
		textMesh,
		"Grid line thickness: " + std::to_string(gridLineThickness).substr(0, std::to_string((int)gridLineThickness).length() + 2),
		textColor,
		textSize,
		(float)winWidth,
		textSize * 2.0f,
		TextAlignment::Right
	);
	RenderTextOnScreen(
		textMesh,
		"Grid rows: " + std::to_string(gridRows),
		textColor,
		textSize,
		(float)winWidth,
		textSize * 3.0f,
		TextAlignment::Right
	);
	RenderTextOnScreen(
		textMesh,
		"Grid cols: " + std::to_string(gridCols),
		textColor,
		textSize,
		(float)winWidth,
		textSize * 4.0f,
		TextAlignment::Right
	);
}