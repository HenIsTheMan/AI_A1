#include <map>

#include "SceneMovement.h"
#include "GL\glew.h"
#include "App.h"

extern int winWidth;
extern int winHeight;

SceneMovement::SceneMovement():
	gridCellWidth(80.0f),
	gridCellHeight(80.0f),
	gridLineThickness(10.0f),
	gridRows(5),
	gridCols(5),
	grid(Grid<float>(0.0f, 0.0f, 0.0f, 0, 0)),
	isDay(false),
	dayNightBT(0.0f),
	objPool(new ObjPool<Entity>())
{
	Math::InitRNG();
}

SceneMovement::~SceneMovement(){
}

void SceneMovement::Update(double dt){
	SceneBase::Update(dt);

	///LMB
	static bool isLMB = false;
	if(!isLMB && App::IsMousePressed(0)){
		isLMB = true;
	} else if(isLMB && !App::IsMousePressed(0)){
		isLMB = false;
	}

	///RMB
	static bool isRMB = false;
	if(!isRMB && App::IsMousePressed(1)){
		isRMB = true;
	} else if(isRMB && !App::IsMousePressed(1)){
		isRMB = false;
	}

	///MMB
	static bool isMMB = false;
	if(!isMMB && App::IsMousePressed(2)){
		isMMB = true;
	} else if(isMMB && !App::IsMousePressed(2)){
		isMMB = false;
	}

	UpdateGrid();
}

void SceneMovement::Render(){
	SceneBase::Render();

	modelStack.PushMatrix();
		modelStack.Translate(im_Cam.pos.x + (float)winWidth * 0.5f, im_Cam.pos.y + (float)winHeight * 0.5f, 0.0f);
		modelStack.Scale((float)winWidth, (float)winHeight, 1.0f);
		RenderMesh(meshList[(int)GeoType::DAY_BG], false);
	modelStack.PopMatrix();

	RenderSceneText();
}

void SceneMovement::UpdateGrid(){
}

void SceneMovement::UpdateEntities(){
}

void SceneMovement::RenderGrid(){
}

void SceneMovement::RenderGridBG(){
}

void SceneMovement::RenderEntities(){
}

void SceneMovement::RenderTranslucentBlock(){
}

void SceneMovement::RenderBG(){
}

void SceneMovement::RenderSceneText(){
	static Mesh* textMesh = meshList[(int)GeoType::TEXT];
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