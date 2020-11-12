#include <map>

#include "SceneMovement.h"
#include "GL\glew.h"
#include "App.h"
#include "SpriteAni.h"

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

	if(dayNightBT <= elapsedTime){
		isDay = !isDay;
		dayNightBT = elapsedTime + 7.0f;
	}

	UpdateGridProperties();
	UpdateGridData();
	UpdateEntities();
}

void SceneMovement::Render(){
	SceneBase::Render();

	RenderGrid();
	RenderGridBG();
	RenderGridData();
	RenderEntities();
	RenderTranslucentBlock();
	RenderBG();
	RenderSceneText();
}

void SceneMovement::UpdateGridProperties(){
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

void SceneMovement::UpdateGridData(){
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

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f;
	const float unitX = gridCellWidth + gridLineThickness;
	const float unitY = gridCellHeight + gridLineThickness;

	const float mouseRow = std::floor(((float)winHeight - (float)mouseY - yOffset - gridLineThickness * 0.5f) / unitY);
	const float mouseCol = std::floor(((float)mouseX - xOffset - gridLineThickness * 0.5f) / unitX);
	const float xTranslate = mouseCol * unitX
		+ xOffset
		+ gridCellWidth * 0.5f
		+ gridLineThickness;
	const float yTranslate = mouseRow * unitY
		+ yOffset
		+ gridCellHeight * 0.5f
		+ gridLineThickness;

	if((float)mouseX > xOffset + gridLineThickness * 0.5f && (float)mouseX < xOffset + gridWidth - gridLineThickness * 0.5f
		&& (float)mouseY > yOffset + gridLineThickness * 0.5f && (float)mouseY < yOffset + gridHeight - gridLineThickness * 0.5f){
		if(isLMB){
			grid.SetData(true, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
		} else if(isRMB){
			grid.SetData(false, (ptrdiff_t)mouseRow, (ptrdiff_t)mouseCol);
		}
	}
}

void SceneMovement::UpdateEntities(){
	static int control = 0;

	if(control != 1){
		Entity* orc = objPool->RetrieveInactiveObj();
		orc->SetType(EntityType::Orc);
		orc->SetLocalPos(2.0f, 1.0f, 0.0f);
		orc->SetLocalScale(1.0f, 1.0f, 1.0f);
		++control;
	}
}

void SceneMovement::RenderGrid(){
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

void SceneMovement::RenderGridBG(){
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

void SceneMovement::RenderGridData(){
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

void SceneMovement::RenderEntities(){
	const std::vector<std::pair<bool, Entity*>>& entityPool = objPool->GetObjPool();
	const size_t& entityPoolSize = entityPool.size();
	const Vector3 posOffset = Vector3(
		(float)winWidth * 0.5f - 2.0f * (gridCellWidth + gridLineThickness),
		(float)winHeight * 0.5f - 2.0f * (gridCellHeight + gridLineThickness),
		0.0f
	);

	for(size_t i = 0; i < entityPoolSize; ++i){
		if(entityPool[i].first){
			const Entity* const& entity = entityPool[i].second;

			const Vector3& entityLocalPos = entity->GetLocalPos();
			const Vector3& entityLocalScale = entity->GetLocalScale();

			const Vector3& entityWorldPos = Vector3(
				posOffset.x + entityLocalPos.x * (gridCellWidth + gridLineThickness),
				posOffset.y + entityLocalPos.y * (gridCellHeight + gridLineThickness),
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

void SceneMovement::RenderTranslucentBlock(){
	double mouseX;
	double mouseY;
	App::GetCursorPos(&mouseX, &mouseY);

	const float gridWidth = grid.CalcWidth();
	const float gridHeight = grid.CalcHeight();

	const float xOffset = ((float)winWidth - gridWidth) * 0.5f;
	const float yOffset = ((float)winHeight - gridHeight) * 0.5f;

	if((float)mouseX > xOffset + gridLineThickness * 0.5f && (float)mouseX < xOffset + gridWidth - gridLineThickness * 0.5f
		&& (float)mouseY > yOffset + gridLineThickness * 0.5f && (float)mouseY < yOffset + gridHeight - gridLineThickness * 0.5f){
		const float unitX = gridCellWidth + gridLineThickness;
		const float unitY = gridCellHeight + gridLineThickness;

		const float mouseRow = std::floor(((float)winHeight - (float)mouseY - yOffset - gridLineThickness * 0.5f) / unitY);
		const float mouseCol = std::floor(((float)mouseX - xOffset - gridLineThickness * 0.5f) / unitX);
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

void SceneMovement::RenderBG(){
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