#include "Scene.h"
#include "GL\glew.h"
#include "App.h"
#include "SpriteAni.h"

#include "EventBlockPlaced.h"
#include "EventGridHeightShrinking.h"
#include "EventGridWidthShrinking.h"
#include "EventCalcActiveObjs.h"
#include "EventCalcInactiveObjs.h"

#include "ListenerFlags.hpp"

#include "StateSkeleCannotMove.h"
#include "StateSkeleIdle.h"
#include "StateSkeleAttack.h"
#include "StateSkeleDead.h"
#include "StateSkeleRevive.h"

#include "StateReptileCannotMove.h"
#include "StateReptileIdle.h"
#include "StateReptileAttack.h"
#include "StateReptileDead.h"
#include "StateReptileMultiply.h"

#include "StateBoyCannotMove.h"
#include "StateBoyIdle.h"
#include "StateBoyAttack.h"
#include "StateBoyDead.h"
#include "StateBoyHeal.h"

#include "StateOrcCannotMove.h"
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
	simStarted(false),
	showLines(false),
	isDay(true),
	dayNightBT(0.0f),
	gameSpd(1.0f),
	objPool(new ObjPool<Entity>()),
	publisher(Publisher::RetrieveGlobalObjPtr()),
	skeleSM(new SM()),
	reptileSM(new SM()),
	boySM(new SM()),
	orcSM(new SM()),
	alphaTeamRegionCase(0),
	omegaTeamRegionCase(0)
{
	Math::InitRNG();

	objPool->CreateObjs(10000);

	skeleSM->AddState(new State(StateID::StateSkeleCannotMove, StateSkeleCannotMove::Enter, StateSkeleCannotMove::Update, StateSkeleCannotMove::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleIdle, StateSkeleIdle::Enter, StateSkeleIdle::Update, StateSkeleIdle::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleAttack, StateSkeleAttack::Enter, StateSkeleAttack::Update, StateSkeleAttack::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleDead, StateSkeleDead::Enter, StateSkeleDead::Update, StateSkeleDead::Exit));
	skeleSM->AddState(new State(StateID::StateSkeleRevive, StateSkeleRevive::Enter, StateSkeleRevive::Update, StateSkeleRevive::Exit));

	reptileSM->AddState(new State(StateID::StateReptileCannotMove, StateReptileCannotMove::Enter, StateReptileCannotMove::Update, StateReptileCannotMove::Exit));
	reptileSM->AddState(new State(StateID::StateReptileIdle, StateReptileIdle::Enter, StateReptileIdle::Update, StateReptileIdle::Exit));
	reptileSM->AddState(new State(StateID::StateReptileAttack, StateReptileAttack::Enter, StateReptileAttack::Update, StateReptileAttack::Exit));
	reptileSM->AddState(new State(StateID::StateReptileDead, StateReptileDead::Enter, StateReptileDead::Update, StateReptileDead::Exit));
	reptileSM->AddState(new State(StateID::StateReptileMultiply, StateReptileMultiply::Enter, StateReptileMultiply::Update, StateReptileMultiply::Exit));

	boySM->AddState(new State(StateID::StateBoyCannotMove, StateBoyCannotMove::Enter, StateBoyCannotMove::Update, StateBoyCannotMove::Exit));
	boySM->AddState(new State(StateID::StateBoyIdle, StateBoyIdle::Enter, StateBoyIdle::Update, StateBoyIdle::Exit));
	boySM->AddState(new State(StateID::StateBoyAttack, StateBoyAttack::Enter, StateBoyAttack::Update, StateBoyAttack::Exit));
	boySM->AddState(new State(StateID::StateBoyDead, StateBoyDead::Enter, StateBoyDead::Update, StateBoyDead::Exit));
	boySM->AddState(new State(StateID::StateBoyHeal, StateBoyHeal::Enter, StateBoyHeal::Update, StateBoyHeal::Exit));

	orcSM->AddState(new State(StateID::StateOrcCannotMove, StateOrcCannotMove::Enter, StateOrcCannotMove::Update, StateOrcCannotMove::Exit));
	orcSM->AddState(new State(StateID::StateOrcIdle, StateOrcIdle::Enter, StateOrcIdle::Update, StateOrcIdle::Exit));
	orcSM->AddState(new State(StateID::StateOrcAttack, StateOrcAttack::Enter, StateOrcAttack::Update, StateOrcAttack::Exit));
	orcSM->AddState(new State(StateID::StateOrcDead, StateOrcDead::Enter, StateOrcDead::Update, StateOrcDead::Exit));
	orcSM->AddState(new State(StateID::StateOrcImmune, StateOrcImmune::Enter, StateOrcImmune::Update, StateOrcImmune::Exit));

	publisher->AddListener((long int)ListenerFlags::ObjPool, objPool);

	grid.SetCellWidth(gridCellWidth);
	grid.SetCellHeight(gridCellHeight);
	grid.SetLineThickness(gridLineThickness);
	grid.SetRows(gridRows);
	grid.SetCols(gridCols);
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

	if(!simStarted && App::Key(VK_SPACE)){
		simStarted = true;
		dayNightBT = elapsedTime + 7.0f;

		alphaTeamRegionCase = Math::RandIntMinMax(1, 4);
		omegaTeamRegionCase = Math::RandIntMinMax(1, 4);
	}

	if(simStarted){
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

		static bool isKeyDownL = false;
		if(!isKeyDownL && App::Key('L')){
			showLines = !showLines;
			isKeyDownL = true;
		} else if(isKeyDownL && !App::Key('L')){
			isKeyDownL = false;
		}
	}

	if(simStarted){
		UpdateGridAttribs();
		UpdateGridBlockData();
		UpdateStates();
		UpdateEntities(dt * gameSpd);
	}
}

void Scene::Render(){
	SceneSupport::Render();

	modelStack.PushMatrix();
	modelStack.Translate(
		-(float)winWidth * 0.5f,
		-(float)winHeight * 0.5f,
		0.0f
	);

	RenderBG();
	if(simStarted){
		RenderGrid();
		RenderRegions();
		RenderGridBlockData();
		RenderTranslucentBlock();
		RenderEntities();
	} else{
		RenderMystery();
	}
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
	ChooseRandDir(entity);
	entity->SetTimeLeft(0.0f);
	entity->SetTeam(EntityTeam::Amt);

	entity->SetStateMachine(skeleSM);
	entity->SetCurrState(skeleSM->GetState(StateID::StateSkeleCannotMove));
	entity->SetNextState(skeleSM->GetState(StateID::StateSkeleCannotMove));
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
	ChooseRandDir(entity);
	entity->SetTimeLeft(0.0f);
	entity->SetTeam(EntityTeam::Amt);

	entity->SetStateMachine(reptileSM);
	entity->SetCurrState(reptileSM->GetState(StateID::StateReptileCannotMove));
	entity->SetNextState(reptileSM->GetState(StateID::StateReptileCannotMove));
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
	ChooseRandDir(entity);
	entity->SetTimeLeft(0.0f);
	entity->SetTeam(EntityTeam::Amt);

	entity->SetStateMachine(boySM);
	entity->SetCurrState(boySM->GetState(StateID::StateBoyCannotMove));
	entity->SetNextState(boySM->GetState(StateID::StateBoyCannotMove));
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
	ChooseRandDir(entity);
	entity->SetTimeLeft(0.0f);
	entity->SetTeam(EntityTeam::Amt);

	entity->SetStateMachine(orcSM);
	entity->SetCurrState(orcSM->GetState(StateID::StateOrcCannotMove));
	entity->SetNextState(orcSM->GetState(StateID::StateOrcCannotMove));
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
				grid.SetCellWidth(++gridCellWidth);
			}
			isKeyDown1 = true;
		} else if(isKeyDown1 && !App::Key('1')){
			isKeyDown1 = false;
		}
		if(!isKeyDown2 && App::Key('2')){
			if(gridCellWidth > gridMinCellWidth){
				grid.SetCellWidth(--gridCellWidth);
			}
			isKeyDown2 = true;
		} else if(isKeyDown2 && !App::Key('2')){
			isKeyDown2 = false;
		}
		if(!isKeyDown3 && App::Key('3')){
			if(gridCellHeight < gridMaxCellHeight){
				grid.SetCellHeight(++gridCellHeight);
			}
			isKeyDown3 = true;
		} else if(isKeyDown3 && !App::Key('3')){
			isKeyDown3 = false;
		}
		if(!isKeyDown4 && App::Key('4')){
			if(gridCellHeight > gridMinCellHeight){
				grid.SetCellHeight(--gridCellHeight);
			}
			isKeyDown4 = true;
		} else if(isKeyDown4 && !App::Key('4')){
			isKeyDown4 = false;
		}
		if(!isKeyDown5 && App::Key('5')){
			if(gridLineThickness < gridMaxLineThickness){
				gridLineThickness += 0.1f;
				grid.SetLineThickness(gridLineThickness);
			}
			isKeyDown5 = true;
		} else if(isKeyDown5 && !App::Key('5')){
			isKeyDown5 = false;
		}
		if(!isKeyDown6 && App::Key('6')){
			if(gridLineThickness > gridMinLineThickness){
				gridLineThickness -= 0.1f;
				grid.SetLineThickness(gridLineThickness);
			}
			isKeyDown6 = true;
		} else if(isKeyDown6 && !App::Key('6')){
			isKeyDown6 = false;
		}
		if(!isKeyDown7 && App::Key('7')){
			if(gridRows < gridMaxRows){
				grid.SetRows(++gridRows);
			}
			isKeyDown7 = true;
		} else if(isKeyDown7 && !App::Key('7')){
			isKeyDown7 = false;
		}
		if(!isKeyDown8 && App::Key('8')){
			if(gridRows > gridMinRows){
				publisher->Notify((long int)ListenerFlags::Entity, new EventGridHeightShrinking(--gridRows), true);
				grid.SetRows(gridRows);
			}
			isKeyDown8 = true;
		} else if(isKeyDown8 && !App::Key('8')){
			isKeyDown8 = false;
		}
		if(!isKeyDown9 && App::Key('9')){
			if(gridCols < gridMaxCols){
				grid.SetCols(++gridCols);
			}
			isKeyDown9 = true;
		} else if(isKeyDown9 && !App::Key('9')){
			isKeyDown9 = false;
		}
		if(!isKeyDown0 && App::Key('0')){
			if(gridCols > gridMinCols){
				publisher->Notify((long int)ListenerFlags::Entity, new EventGridWidthShrinking(--gridCols), true);
				grid.SetCols(gridCols);
			}
			isKeyDown0 = true;
		} else if(isKeyDown0 && !App::Key('0')){
			isKeyDown0 = false;
		}
}

void Scene::UpdateGridBlockData(){
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
			grid.SetBlockData(true, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
			publisher->Notify((long int)ListenerFlags::Entity, new EventBlockPlaced((int)mouseRow, (int)mouseCol), true);
		} else if(isRMB){
			grid.SetBlockData(false, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
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
	StateSkeleCannotMove* const stateSkeleCannotMove = ((StateSkeleCannotMove*)skeleSM->GetState(StateID::StateSkeleCannotMove));
	stateSkeleCannotMove->im_ElapsedTime = elapsedTime;
	stateSkeleCannotMove->im_Grid = &grid;
	stateSkeleCannotMove->im_GridRows = gridRows;
	stateSkeleCannotMove->im_GridCols = gridCols;

	StateSkeleIdle* const stateSkeleIdle = ((StateSkeleIdle*)skeleSM->GetState(StateID::StateSkeleIdle));
	stateSkeleIdle->im_ElapsedTime = elapsedTime;
	stateSkeleIdle->im_Grid = &grid;
	stateSkeleIdle->im_GridRows = gridRows;
	stateSkeleIdle->im_GridCols = gridCols;

	StateSkeleDead* const stateSkeleDead = ((StateSkeleDead*)skeleSM->GetState(StateID::StateSkeleDead));
	stateSkeleDead->im_ObjPool = objPool;
}

void Scene::UpdateReptileStates(){
	StateReptileCannotMove* const stateReptileCannotMove = ((StateReptileCannotMove*)reptileSM->GetState(StateID::StateReptileCannotMove));
	stateReptileCannotMove->im_ElapsedTime = elapsedTime;
	stateReptileCannotMove->im_Grid = &grid;
	stateReptileCannotMove->im_GridRows = gridRows;
	stateReptileCannotMove->im_GridCols = gridCols;

	StateReptileIdle* const stateReptileIdle = ((StateReptileIdle*)reptileSM->GetState(StateID::StateReptileIdle));
	stateReptileIdle->im_ElapsedTime = elapsedTime;
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
	StateBoyCannotMove* const stateBoyCannotMove = ((StateBoyCannotMove*)boySM->GetState(StateID::StateBoyCannotMove));
	stateBoyCannotMove->im_ElapsedTime = elapsedTime;
	stateBoyCannotMove->im_Grid = &grid;
	stateBoyCannotMove->im_GridRows = gridRows;
	stateBoyCannotMove->im_GridCols = gridCols;

	StateBoyIdle* const stateBoyIdle = ((StateBoyIdle*)boySM->GetState(StateID::StateBoyIdle));
	stateBoyIdle->im_ElapsedTime = elapsedTime;
	stateBoyIdle->im_Grid = &grid;
	stateBoyIdle->im_GridRows = gridRows;
	stateBoyIdle->im_GridCols = gridCols;

	StateBoyDead* const stateBoyDead = ((StateBoyDead*)boySM->GetState(StateID::StateBoyDead));
	stateBoyDead->im_ObjPool = objPool;
}

void Scene::UpdateOrcStates(){
	StateOrcCannotMove* const stateOrcCannotMove = ((StateOrcCannotMove*)orcSM->GetState(StateID::StateOrcCannotMove));
	stateOrcCannotMove->im_ElapsedTime = elapsedTime;
	stateOrcCannotMove->im_Grid = &grid;
	stateOrcCannotMove->im_GridRows = gridRows;
	stateOrcCannotMove->im_GridCols = gridCols;

	StateOrcIdle* const stateOrcIdle = ((StateOrcIdle*)orcSM->GetState(StateID::StateOrcIdle));
	stateOrcIdle->im_ElapsedTime = elapsedTime;
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
		skele->SetTeam(rand() & 1 ? EntityTeam::Alpha : EntityTeam::Omega);
		//skele->SetNextState(skele->GetStateMachine()->GetState(StateID::StateSkeleIdle));
		publisher->AddListener((long int)ListenerFlags::Skele | (long int)ListenerFlags::Entity, skele);

		Entity* reptile = CreateReptile({
			Vector3(15.0f, 12.0f, 0.0f)
		});
		reptile->SetTeam(rand() & 1 ? EntityTeam::Alpha : EntityTeam::Omega);
		reptile->SetTarget(skele);
		//reptile->SetNextState(reptile->GetStateMachine()->GetState(StateID::StateReptileIdle));
		publisher->AddListener((long int)ListenerFlags::Reptile | (long int)ListenerFlags::Entity, reptile);

		Entity* boy = CreateBoy({
			Vector3(5.0f, 4.0f, 0.0f)
		});
		boy->SetTeam(rand() & 1 ? EntityTeam::Alpha : EntityTeam::Omega);
		//boy->SetNextState(boy->GetStateMachine()->GetState(StateID::StateBoyIdle));
		publisher->AddListener((long int)ListenerFlags::Boy | (long int)ListenerFlags::Entity, boy);

		Entity* orc = CreateOrc({
			Vector3(18.0f, 3.0f, 0.0f)
		});
		orc->SetTeam(rand() & 1 ? EntityTeam::Alpha : EntityTeam::Omega);
		//orc->SetNextState(orc->GetStateMachine()->GetState(StateID::StateOrcIdle));
		publisher->AddListener((long int)ListenerFlags::Orc | (long int)ListenerFlags::Entity, orc);

		++control;
	}

	std::vector<std::pair<bool, Entity*>>& entityPool = objPool->RetrievePool();
	const size_t& entityPoolSize = entityPool.size();

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			Entity* const entity = entityPool[i].second;

			bool shldContinue = false;
			const Event* myEvent = nullptr;
			EventID ID = EventID::Amt;
			do{
				myEvent = entity->FetchEvent();
				if(myEvent){
					ID = myEvent->GetID();

					switch(entity->OnEvent(myEvent, true)){
						case -5:
							objPool->DeactivateObj(entity);
							shldContinue = true;
							break;
					}
				}
			} while(myEvent
				&& (ID == EventID::EventBlockPlaced
				|| ID == EventID::EventGridHeightShrinking
				|| ID == EventID::EventGridWidthShrinking)
			); //Important events must all be processed

			if(shldContinue){
				continue;
			}

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
			0.05f
		);
		modelStack.Scale(
			gridLineThickness,
			gridHeight,
			1.0f
		);
		RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.5f, 0.5f, 0.5f), 1.0f);
		modelStack.PopMatrix();
	}

	const int amtOfHorizLines = grid.CalcAmtOfHorizLines();
	for(int i = 0; i < amtOfHorizLines; ++i){
		modelStack.PushMatrix();
		modelStack.Translate(
			(float)winWidth * 0.5f,
			yOffset + (gridCellHeight + gridLineThickness) * (float)i,
			0.05f
		);
		modelStack.Scale(
			gridWidth,
			gridLineThickness,
			1.0f
		);
		RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.5f, 0.5f, 0.5f), 1.0f);
		modelStack.PopMatrix();
	}
}

void Scene::RenderMystery(){
	modelStack.PushMatrix();
	modelStack.Translate(
		(float)winWidth * 0.5f,
		(float)winHeight * 0.5f,
		0.05f
	);
	modelStack.Scale(
		grid.CalcWidth(),
		grid.CalcHeight(),
		1.0f
	);
	RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.5f, 0.5f, 0.5f), 1.0f);
	modelStack.PopMatrix();
}

void Scene::RenderGridBlockData(){
	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f + gridLineThickness + gridCellWidth * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f + gridLineThickness + gridCellHeight * 0.5f;

	const std::vector<std::vector<bool>>& gridBlockData = grid.GetBlockData();

	for(int i = 0; i < gridRows; ++i){
		for(int j = 0; j < gridCols; ++j){
			if(gridBlockData[i][j]){
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
	static std::string stateTexts[(int)StateID::Amt]{
		"StateSkeleCannotMove",
		"StateSkeleIdle",
		"StateSkeleAttack",
		"StateSkeleDead",
		"StateSkeleRevive",

		"StateReptileCannotMove",
		"StateReptileIdle",
		"StateReptileAttack",
		"StateReptileDead",
		"StateReptileMultiply",

		"StateBoyCannotMove",
		"StateBoyIdle",
		"StateBoyAttack",
		"StateBoyDead",
		"StateBoyHeal",

		"StateOrcCannotMove",
		"StateOrcIdle",
		"StateOrcAttack",
		"StateOrcDead",
		"StateOrcImmune"
	};

	const std::vector<std::pair<bool, Entity*>>& entityPool = objPool->GetPool();
	const size_t& entityPoolSize = entityPool.size();

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xPosOffset = ((float)winWidth - gridWidth) * 0.5f + gridCellWidth * 0.5f + gridLineThickness;
	const float yPosOffset = ((float)winHeight - gridHeight) * 0.5f + gridCellHeight * 0.5f + gridLineThickness;

	static float individualDepthOffset = 0.0f;
	float opacity;

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			opacity = 1.0f;
			const Entity* const entity = entityPool[i].second;
			const Vector3& entityLocalPos = entity->GetLocalPos();
			const Vector3& entityLocalScale = entity->GetLocalScale();

			Vector3 entityWorldPos = Vector3(
				xPosOffset + entityLocalPos.x * (gridCellWidth + gridLineThickness),
				yPosOffset + entityLocalPos.y * (gridCellHeight + gridLineThickness),
				0.2f + individualDepthOffset
			);
			const Vector3 entityWorldScale = Vector3(
				entityLocalScale.x * gridCellWidth,
				entityLocalScale.y * gridCellHeight,
				1.0f
			);

			///Render entity-to-target line
			if(showLines){
				glDepthFunc(GL_LEQUAL);
				const Entity* const entityTarget = entity->GetTarget();

				if(entityTarget){
					const Vector3 vec = entity->GetTarget()->GetLocalPos() - entity->GetLocalPos();
					modelStack.PushMatrix();

					modelStack.Translate(
						entityWorldPos.x + vec.x * 0.5f * (gridCellWidth + gridLineThickness),
						entityWorldPos.y + vec.y * 0.5f * (gridCellHeight + gridLineThickness),
						1.0f
					);
					modelStack.Rotate(
						Math::RadianToDegree(atan2(vec.y, vec.x)),
						0.0f,
						0.0f,
						1.0f
					);
					modelStack.Scale(
						vec.Length() * (gridCellWidth + gridLineThickness),
						1.0f,
						1.0f
					);

					RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.0f, 1.0f, 1.0f), 1.0f);
					modelStack.PopMatrix();
				}
				glDepthFunc(GL_LESS);
			}

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

			///Render health, health bar and text
			const float ratio = (float)entity->GetCurrHealth() / (float)entity->GetMaxHealth();

			modelStack.PushMatrix();

			modelStack.Translate(
				0.0f,
				0.3f,
				0.2f + individualDepthOffset
			);
			modelStack.Scale(
				0.9f,
				0.05f,
				1.0f
			);

			modelStack.PushMatrix();

			modelStack.Translate(
				0.0f,
				0.4f,
				0.0f
			);
			modelStack.Scale(
				0.2f,
				4.0f,
				1.0f
			);

			RenderText(
				entity->GetTeam() == EntityTeam::Alpha ? meshList[(int)GeoType::TextMod2] : meshList[(int)GeoType::TextMod1],
				stateTexts[(int)entity->GetCurrState()->GetID()],
				entity->GetTeam() == EntityTeam::Alpha ? Color() : Color(0.0f, 0.0f, 0.0f),
				TextAlignment::Center
			);
			modelStack.PopMatrix();

			modelStack.PushMatrix();

			modelStack.Translate(
				-(1.f - ratio) * 0.5f,
				0.0f,
				0.0f
			);
			modelStack.Scale(
				ratio - 0.05f,
				0.5f,
				1.0f
			);

			RenderMesh(meshList[(int)GeoType::Quad], true, Color(1.0f - ratio, ratio, 0.0f), opacity);
			modelStack.PopMatrix();

			RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.1f, 0.1f, 0.1f), opacity);
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

void Scene::RenderRegions(){
	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	float alphaPosX;
	float alphaPosY;
	float alphaScaleX;
	float alphaScaleY;
	float omegaPosX;
	float omegaPosY;
	float omegaScaleX;
	float omegaScaleY;

	switch(alphaTeamRegionCase){
		case 1:
			alphaPosX = (float)winWidth * 0.5f - gridWidth * 0.25f;
			alphaPosY = (float)winHeight * 0.5f;
			alphaScaleX = gridWidth * 0.5f;
			alphaScaleY = gridHeight;

			omegaPosX = (float)winWidth * 0.5f + gridWidth * 0.25f;
			omegaPosY = (float)winHeight * 0.5f;
			omegaScaleX = gridWidth * 0.5f;
			omegaScaleY = gridHeight;
			break;
		case 2:
			alphaPosX = (float)winWidth * 0.5f + gridWidth * 0.25f;
			alphaPosY = (float)winHeight * 0.5f;
			alphaScaleX = gridWidth * 0.5f;
			alphaScaleY = gridHeight;

			omegaPosX = (float)winWidth * 0.5f - gridWidth * 0.25f;
			omegaPosY = (float)winHeight * 0.5f;
			omegaScaleX = gridWidth * 0.5f;
			omegaScaleY = gridHeight;
			break;
		case 3:
			alphaPosX = (float)winWidth * 0.5f;
			alphaPosY = (float)winHeight * 0.5f - gridHeight * 0.25f;
			alphaScaleX = gridWidth;
			alphaScaleY = gridHeight * 0.5f;

			omegaPosX = (float)winWidth * 0.5f;
			omegaPosY = (float)winHeight * 0.5f + gridHeight * 0.25f;
			omegaScaleX = gridWidth;
			omegaScaleY = gridHeight * 0.5f;
			break;
		case 4:
			alphaPosX = (float)winWidth * 0.5f;
			alphaPosY = (float)winHeight * 0.5f + gridHeight * 0.25f;
			alphaScaleX = gridWidth;
			alphaScaleY = gridHeight * 0.5f;

			omegaPosX = (float)winWidth * 0.5f;
			omegaPosY = (float)winHeight * 0.5f - gridHeight * 0.25f;
			omegaScaleX = gridWidth;
			omegaScaleY = gridHeight * 0.5f;
			break;
		default:
			assert(false);
	}

	modelStack.PushMatrix();
	modelStack.Translate(
		alphaPosX,
		alphaPosY,
		0.05f
	);
	modelStack.Scale(
		alphaScaleX,
		alphaScaleY,
		1.0f
	);
	RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.7f, 0.7f, 0.7f), 0.8f);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(
		omegaPosX,
		omegaPosY,
		0.05f
	);
	modelStack.Scale(
		omegaScaleX,
		omegaScaleY,
		1.0f
	);
	RenderMesh(meshList[(int)GeoType::Quad], true, Color(0.3f, 0.3f, 0.3f), 0.8f);
	modelStack.PopMatrix();
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

	if(!simStarted){
		RenderTextOnScreen(
			textMesh,
			"Press Space to start!",
			Color(0.0f, 0.0f, 0.0f),
			((sinf(elapsedTime * 4.0f) + 1.0f) * 0.5f + 1.0f) * 0.5f * textSize,
			(float)winWidth * 0.5f,
			textSize * 18.75f,
			TextAlignment::Center
		);
		RenderTextOnScreen(
			textMesh,
			"Press Space to start!",
			Color(),
			((cosf(elapsedTime * 4.0f) + 1.0f) * 0.5f  + 1.0f) * 0.5f * textSize,
			(float)winWidth * 0.5f,
			textSize * 0.25f,
			TextAlignment::Center
		);
	}

	RenderDebugInfoText(textMesh, Color(1.0f, 0.5f, 0.0f), textSize);
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
		"Inactive objs: " + std::to_string(publisher->Notify((long int)ListenerFlags::ObjPool, new EventCalcInactiveObjs(), false)),
		textColor,
		textSize,
		0.0f,
		textSize * 3.0f
	);
	RenderTextOnScreen(
		textMesh,
		"Active objs: " + std::to_string(publisher->Notify((long int)ListenerFlags::ObjPool, new EventCalcActiveObjs(), false)),
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
	RenderTextOnScreen(
		textMesh,
		"L: Toggle entity-to-target lines",
		textColor,
		textSize,
		0.0f,
		textSize * 12.0f
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