#include <map>
#include <sstream>

#include "SceneMovement.h"
#include "GL\glew.h"
#include "Application.h"

#include "StatesFish.h"
#include "StatesShark.h"

void SceneMovement::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();
	
	m_objectCount = 0;
	m_noGrid = 20;
	m_gridSize = m_worldHeight / m_noGrid;
	m_gridOffset = m_gridSize / 2;
	m_hourOfTheDay = 0;

	im_FishCount = 0;
	im_DiedByHunger = 0;
	im_EatenByShark = 0;
	im_Overeat = 0;

	fishSM = new StateMachine();
	fishSM->AddState(new StateTooFull("StateTooFull"));
	fishSM->AddState(new StateFull("StateFull"));
	fishSM->AddState(new StateHungry("StateHungry"));
	fishSM->AddState(new StateDead("StateDead"));

	sharkSM = new StateMachine();
	sharkSM ->AddState(new StateCrazy("StateCrazy"));
	sharkSM ->AddState(new StateNaughty("StateNaughty"));
	sharkSM ->AddState(new StateHappy("StateHappy"));
}

GameObject* SceneMovement::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && type == go->type)
		{
			go->active = true;
			++m_objectCount;
			if(go->type == GameObject::GO_FISH){
				++im_FishCount;
			}
			return go;
		}
	}
	for(int i = 0; i < 5; ++i){
		GameObject *go = new GameObject(type);
		if(go->type == GameObject::GO_FISH){
			go->sm = fishSM;
		} else if(go->type == GameObject::GO_SHARK){
			go->sm = sharkSM;
		}
		m_goList.emplace_back(go);
	}
	return FetchGO(type);
}

void SceneMovement::Update(double dt){
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	
	static bool isPressedPlus = false;
	static bool isPressedMinus = false;
	if(!isPressedPlus && Application::IsKeyPressed(VK_OEM_PLUS)){
		m_speed += 0.1f;
		isPressedPlus = true;
	} else if(isPressedPlus && !Application::IsKeyPressed(VK_OEM_PLUS)){
		isPressedPlus = false;
	}
	if(!isPressedMinus && Application::IsKeyPressed(VK_OEM_MINUS)){
		m_speed = Math::Max(0.f, m_speed - 0.1f);
		isPressedMinus = true;
	} else if(isPressedMinus && !Application::IsKeyPressed(VK_OEM_MINUS)){
		isPressedMinus = false;
	}

	static bool isPressedLMB = false;
	static bool isPressedRMB = false;
	static bool isPressedMMB = false;

	///LMB
	if(!isPressedLMB && Application::IsMousePressed(0)){
		isPressedLMB = true;

		GameObject *go = FetchGO(GameObject::GO_FISH);
		go->id = m_objectCount;
		go->pos.Set(m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, 0);
		go->scale.Set(m_gridSize, m_gridSize, m_gridSize);
		go->target = go->pos;
		go->steps = 0;
		go->energy = 8.0f;
		go->moveSpeed = 5.0f;
		go->currState = go->nextState = go->sm->GetState("StateFull");
	} else if(isPressedLMB && !Application::IsMousePressed(0)){
		isPressedLMB = false;
	}

	///RMB
	if(!isPressedRMB && Application::IsMousePressed(1)){
		isPressedRMB = true;

		GameObject *go = FetchGO(GameObject::GO_FISHFOOD);
		go->id = m_objectCount;
		go->scale.Set(m_gridSize, m_gridSize, m_gridSize);
		go->pos.Set(m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, 0);
		go->target = go->pos;
		go->steps = 0;
		go->energy = 8.0f;
		go->moveSpeed = 2.0f;
	} else if(isPressedRMB && !Application::IsMousePressed(1)){
		isPressedRMB = false;
	}

	///MMB
	if(!isPressedMMB && Application::IsMousePressed(2)){
		isPressedMMB = true;

		GameObject *go = FetchGO(GameObject::GO_SHARK);
		go->id = m_objectCount;
		go->scale.Set(m_gridSize, m_gridSize, m_gridSize);
		go->pos.Set(m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, m_gridOffset + (float)Math::RandIntMinMax(0, m_noGrid - 1) * m_gridSize, 0);
		go->target = go->pos;
		go->steps = 0;
		go->energy = 8.0f;
		go->moveSpeed = 10.0f;
		go->currState = go->nextState = go->sm->GetState("StateHappy");
	} else if(isPressedMMB && !Application::IsMousePressed(2)){
		isPressedMMB = false;
	}

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it){
		GameObject* const& go = *it;
		if(go->active){
			if(go->type == GameObject::GO_FISH){
				go->SetNextState();
				go->sm->Update(go, dt * m_speed);

				const std::string currStateID = go->currState->GetStateID();

				///External triggers
				if(currStateID != "StateDead"){
					for(std::vector<GameObject*>::iterator iter = m_goList.begin(); iter != m_goList.end(); ++iter){
						GameObject* other = *iter;
						if(other->active && other != go && (go->pos - other->pos).LengthSquared() < m_gridSize * m_gridSize){
							switch(other->type){
								case GameObject::GO_FISHFOOD:
									go->energy += 4.0f;
									other->active = false;
									--m_objectCount;
									break;
								case GameObject::GO_SHARK:
									go->energy = -1.0f;
									go->nextState = go->sm->GetState("StateDead");
									++im_EatenByShark;
									break;
							}
						}
					}
				}

				if(currStateID == "StateFull"){
					Vector3 dir = go->target - go->pos;
					if(dir.Length() < go->moveSpeed * (float)dt * m_speed){
						go->pos = go->target;

						std::map<float, GameObject*> sharks;
						for(std::vector<GameObject*>::iterator iter = m_goList.begin(); iter != m_goList.end(); ++iter){
							GameObject* const& other = *iter;
							if(other->active && other != go && other->type == GameObject::GO_SHARK){
								sharks[(Vector3(other->pos.x, other->pos.y, 0.0f) - Vector3(go->pos.x, go->pos.y, 0.0f)).LengthSquared()] = other;
							}
						}
						if(!sharks.empty()){
							auto pair = *sharks.begin();
							const float& closestDist = pair.first;
							const GameObject* const& closestShark = pair.second;
							if(closestDist > Math::EPSILON && closestDist <= (m_gridSize * 5.0f) * (m_gridSize * 5.0f)){ //Avoid shark
								const Vector3 vec = go->pos - closestShark->pos;
								if(fabs(vec.x) > fabs(vec.y)){
									go->target.x += (closestShark->pos.x < go->pos.x ? m_gridSize : -m_gridSize);
								} else{
									go->target.y += (closestShark->pos.y < go->pos.y ? m_gridSize : -m_gridSize);
								}
								std::cout << go->id << " Avoiding shark...\n";
							} else{
								ChooseRandDir(go);
							}
						} else{
							ChooseRandDir(go);
						}
					} else{
						Move(go, dir, dt);
					}

					if(go->energy >= 10.0f){
						++im_Overeat;
					}
				} else if(currStateID == "StateHungry"){
					Vector3 dir = go->target - go->pos;
					if(dir.Length() < go->moveSpeed * (float)dt * m_speed){
						go->pos = go->target;

						std::map<float, GameObject*> food;
						for(std::vector<GameObject*>::iterator iter = m_goList.begin(); iter != m_goList.end(); ++iter){
							GameObject* const& other = *iter;
							if(other->active && other != go && other->type == GameObject::GO_FISHFOOD){
								food[(Vector3(other->pos.x, other->pos.y, 0.0f) - Vector3(go->pos.x, go->pos.y, 0.0f)).LengthSquared()] = other;
							}
						}
						if(!food.empty()){
							auto pair = *food.begin();
							const float& closestDist = pair.first;
							const GameObject* const& closestFood = pair.second;
							if(closestDist > Math::EPSILON && closestDist <= (m_gridSize * 5.0f) * (m_gridSize * 5.0f)){ //Hunt for food
								const Vector3 vec = go->pos - closestFood->pos;
								if(fabs(vec.x) > fabs(vec.y)){
									go->target.x += (closestFood->pos.x < go->pos.x ? -m_gridSize : m_gridSize);
								} else{
									go->target.y += (closestFood->pos.y < go->pos.y ? -m_gridSize : m_gridSize);
								}
								std::cout << go->id << " Chasing food...\n";
							} else{
								ChooseRandDir(go);
							}
						} else{
							ChooseRandDir(go);
						}
					} else{
						Move(go, dir, dt);
					}

					if(go->energy <= 0.0f){
						++im_DiedByHunger;
						go->countDown = 3.0f;
					}
				} else if(currStateID == "StateDead"){
					go->countDown -= (float)dt;
					if(go->countDown < 0.0f){
						go->active = false;
						--m_objectCount;
						--im_FishCount;
					}
				}
			} else if(go->type == GameObject::GO_SHARK){
				go->SetNextState();
				go->sm->Update(go, dt * m_speed);

				const std::string currStateID = go->currState->GetStateID();

				if(currStateID == "StateCrazy"){
					if(im_FishCount <= 10){
						go->nextState = go->sm->GetState("StateNaughty");
						continue;
					}

					Vector3 dir = go->target - go->pos;
					if(dir.Length() < go->moveSpeed * (float)dt * m_speed){
						go->pos = go->target;

						GameObject* highestEnergyFish = nullptr;
						for(std::vector<GameObject*>::iterator iter = m_goList.begin(); iter != m_goList.end(); ++iter){
							GameObject* const& other = *iter;
							if(other->active && other != go && other->type == GameObject::GO_FISH){
								if(!highestEnergyFish || (highestEnergyFish && highestEnergyFish->energy < other->energy)){
									highestEnergyFish = other;
								}
							}
						}
						if(highestEnergyFish){
							const Vector3 vec = go->pos - highestEnergyFish->pos;
							if(fabs(vec.x) > fabs(vec.y)){
								go->target.x += (highestEnergyFish->pos.x < go->pos.x ? -m_gridSize : m_gridSize);
							} else{
								go->target.y += (highestEnergyFish->pos.y < go->pos.y ? -m_gridSize : m_gridSize);
							}
							std::cout << go->id << " Chasing fish with highest energy...\n";
						} else{
							ChooseRandDir(go);
						}
					} else{
						Move(go, dir, dt);
					}
				} else if(currStateID == "StateNaughty"){
					if(im_FishCount > 10){
						go->nextState = go->sm->GetState("StateCrazy");
						continue;
					} else if(im_FishCount <= 4){
						go->nextState = go->sm->GetState("StateHappy");
						continue;
					}

					Vector3 dir = go->target - go->pos;
					if(dir.Length() < go->moveSpeed * (float)dt * m_speed){
						go->pos = go->target;

						GameObject* nearestFedFish = nullptr;
						for(std::vector<GameObject*>::iterator iter = m_goList.begin(); iter != m_goList.end(); ++iter){
							GameObject* const& other = *iter;
							if(other->active && other != go && other->type == GameObject::GO_FISH){
								const std::string otherCurrStateID = other->currState->GetStateID();
								if(otherCurrStateID == "StateTooFull" || otherCurrStateID == "StateFull"){
									if(!nearestFedFish || (nearestFedFish
										&& (Vector3(nearestFedFish->pos.x, nearestFedFish->pos.y, 0.0f) - Vector3(go->pos.x, go->pos.y, 0.0f)).LengthSquared()
										> (Vector3(other->pos.x, other->pos.y, 0.0f) - Vector3(go->pos.x, go->pos.y, 0.0f)).LengthSquared())){
										nearestFedFish = other;
									}
								}
							}
						}
						if(nearestFedFish){
							const Vector3 vec = go->pos - nearestFedFish->pos;
							if(fabs(vec.x) > fabs(vec.y)){
								go->target.x += (nearestFedFish->pos.x < go->pos.x ? -m_gridSize : m_gridSize);
							} else{
								go->target.y += (nearestFedFish->pos.y < go->pos.y ? -m_gridSize : m_gridSize);
							}
							std::cout << go->id << " Chasing nearest fed fish...\n";
						} else{
							ChooseRandDir(go);
						}
					} else{
						Move(go, dir, dt);
					}
				} else if(currStateID == "StateHappy"){
					if(im_FishCount > 4){
						go->nextState = go->sm->GetState("StateNaughty");
						continue;
					}
					goto moveRandomly;
				}
			} else{
				moveRandomly:
				Vector3 dir = go->target - go->pos;
				if(dir.Length() < go->moveSpeed * (float)dt * m_speed){
					go->pos = go->target;
					ChooseRandDir(go);
				} else{
					Move(go, dir, dt);
				}
			}

			///Bounds checking
			go->energy = Math::Max(go->energy, 0.0f);
			go->pos.x = Math::Clamp(go->pos.x, m_gridOffset, m_gridOffset + m_gridSize * float(m_noGrid - 1));
			go->pos.y = Math::Clamp(go->pos.y, m_gridOffset, m_gridOffset + m_gridSize * float(m_noGrid - 1));
		}
	}
}

void SceneMovement::RenderGO(GameObject *go)
{
	switch(go->type)
	{
		case GameObject::GO_FISH: {
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, (float)go->id * 0.1f);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);

			const std::string stateID = go->currState->GetStateID();
			if(stateID == "StateTooFull"){
				RenderMesh(meshList[GEO_FISHTOOFULL], false);
			} else if(stateID == "StateFull"){
				RenderMesh(meshList[GEO_FISHFULL], false);
			} else if(stateID == "StateHungry"){
				RenderMesh(meshList[GEO_FISHHUNGRY], false);
			} else if(stateID == "StateDead"){
				RenderMesh(meshList[GEO_FISHDEAD], false);
			}

			std::ostringstream ss;
			modelStack.PushMatrix();
				modelStack.Translate(0.3f, 0.8f, 0.0f);
				ss << "ID: " << go->id;
				RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
				ss.str("");
			modelStack.PopMatrix();
			modelStack.PushMatrix();
				modelStack.Translate(0.3f, -0.8f, 0.0f);
				ss << go->energy;
				RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
				ss.str("");
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
		case GameObject::GO_SHARK: {
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, (float)go->id * 0.1f);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);

			const std::string stateID = go->currState->GetStateID();
			if(stateID == "StateCrazy"){
				RenderMesh(meshList[GEO_SHARKCRAZY], false);
			} else if(stateID == "StateNaughty"){
				RenderMesh(meshList[GEO_SHARKNAUGHTY], false);
			} else if(stateID == "StateHappy"){
				RenderMesh(meshList[GEO_SHARKHAPPY], false);
			}

			std::ostringstream ss;
			modelStack.PushMatrix();
			modelStack.Translate(0.3f, 0.8f, 0.0f);
			ss << "ID: " << go->id;
			RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
		}
		case GameObject::GO_FISHFOOD:
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, (float)go->id * 0.1f);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(meshList[GEO_FISHFOOD], false);

			std::ostringstream ss;
			modelStack.PushMatrix();
			modelStack.Translate(0.3f, 0.8f, 0.0f);
			ss << "ID: " << go->id;
			RenderText(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0));
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			break;
	}
}

void SceneMovement::Render()
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
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "LMB to spawn fish", Color(0, 1, 0), 3, 50, 27);

	RenderTextOnScreen(meshList[GEO_TEXT], "RMB to spawn food", Color(0, 1, 0), 3, 50, 24);

	RenderTextOnScreen(meshList[GEO_TEXT], "MMB to spawn shark", Color(0, 1, 0), 3, 50, 21);

	RenderTextOnScreen(meshList[GEO_TEXT], (std::string)" + " + (std::string)"Game Spd: "
		+ std::to_string(m_speed).substr(0, std::to_string((int)m_speed).length() + 2)
		+ (std::string)" - ", Color(0, 1, 0), 3, 50, 3);

	std::ostringstream ss;
	
	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 0);

	ss.str("");
	ss << "Obj count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss << "DiedByHunger count: " << im_DiedByHunger;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 9);

	ss.str("");
	ss << "EatenByShark count: " << im_EatenByShark;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 15);

	ss.str("");
	ss << "Overeat count: " << im_Overeat;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 12);

	ss.str("");
	ss << "Fish count: " << im_FishCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 18);
}

void SceneMovement::Exit()
{
	SceneBase::Exit();

	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}

	if(fishSM){
		delete fishSM;
		fishSM = nullptr;
	}
	if(sharkSM){
		delete sharkSM;
		sharkSM = nullptr;
	}

	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}

void SceneMovement::ChooseRandDir(GameObject* go){
	switch(Math::RandIntMinMax(0, 3)){
		case 0:
			go->target.x += m_gridSize;
			break;
		case 1:
			go->target.x -= m_gridSize;
			break;
		case 2:
			go->target.y += m_gridSize;
			break;
		case 3:
			go->target.y -= m_gridSize;
			break;
	}
}

void SceneMovement::Move(GameObject* go, Vector3& dir, double dt){
	try{
		dir.Normalize();
	} catch(const DivideByZero&){}
	go->pos += go->moveSpeed * dir * (float)dt * m_speed;
}