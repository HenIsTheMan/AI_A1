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

	objPool->CreateObjs(10000);
}

SceneMovement::~SceneMovement(){
	if(objPool){
		delete objPool;
		objPool = nullptr;
	}
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

	if(dayNightBT <= elapsedTime){
		isDay = !isDay;
		dayNightBT = elapsedTime + 7.0f;
	}

	UpdateGrid();

	//const float gridWidth = grid.CalcWidth();
	//const float gridHeight = grid.CalcHeight();

	//const float xOffset = ((float)winWidth - gridWidth) * 0.5f;
	//const float yOffset = ((float)winHeight - gridHeight) * 0.5f;
	//const float unitX = gridCellWidth + gridLineThickness;
	//const float unitY = gridCellHeight + gridLineThickness;

	//const float mouseRow = std::floor((winHeight - lastY - yOffset - gridLineThickness * 0.5f) / unitY);
	//const float mouseCol = std::floor((lastX - xOffset - gridLineThickness * 0.5f) / unitX);
	//const float xTranslate = mouseCol * unitX
	//	+ xOffset
	//	+ gridCellWidth * 0.5f
	//	+ gridLineThickness;
	//const float yTranslate = mouseRow * unitY
	//	+ yOffset
	//	+ gridCellHeight * 0.5f
	//	+ gridLineThickness;

	//if(lastX > xOffset + gridLineThickness * 0.5f && lastX < xOffset + gridWidth - gridLineThickness * 0.5f
	//	&& lastY > yOffset + gridLineThickness * 0.5f && lastY < yOffset + gridHeight - gridLineThickness * 0.5f){
	//	if(LMB){
	//		Entity* const& entity = objPool->RetrieveInactiveObj();
	//		entity->RetrieveType() = EntityType::Block;
	//		entity->RetrievePos() = glm::vec3(xTranslate, yTranslate, 0.0f);
	//	} else if(RMB){
	//		//grid.SetData(EntityType::Null, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
	//	}
	//}

	UpdateEntities();
}

void SceneMovement::Render(){
	SceneBase::Render();

	RenderGrid();
	RenderGridBG();
	RenderEntities();
	RenderTranslucentBlock();
	RenderBG();
	RenderSceneText();
}

void SceneMovement::UpdateGrid(){
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
		++gridRows;
		isKeyDown7 = true;
	} else if(isKeyDown7 && !App::Key('7')){
		isKeyDown7 = false;
	}
	if(!isKeyDown8 && App::Key('8')){
		--gridRows;
		isKeyDown8 = true;
	} else if(isKeyDown8 && !App::Key('8')){
		isKeyDown8 = false;
	}
	if(!isKeyDown9 && App::Key('9')){
		++gridCols;
		isKeyDown9 = true;
	} else if(isKeyDown9 && !App::Key('9')){
		isKeyDown9 = false;
	}
	if(!isKeyDown0 && App::Key('0')){
		--gridCols;
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
	modelStack.PushMatrix();
		modelStack.Translate(im_Cam.pos.x + (float)winWidth * 0.5f, im_Cam.pos.y + (float)winHeight * 0.5f, 0.0f);
		modelStack.Scale((float)winWidth, (float)winHeight, 1.0f);
		RenderMesh(meshList[(int)GeoType::DayBG], false);
	modelStack.PopMatrix();
}

void SceneMovement::RenderSceneText(){
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