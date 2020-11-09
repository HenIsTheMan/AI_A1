#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.h"
#include "MeshBuilder.h"
#include "App.h"
#include "LoadImg.h"

extern int winWidth;
extern int winHeight;

static const int fontWidth[] = { 0,26,26,26,26,26,26,26,26,26,26,26,26,0,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,12,17,21,26,26,37,35,11,16,16,26,26,13,16,13,20,26,26,26,26,26,26,26,26,26,26,14,14,26,26,26,24,46,30,28,28,32,25,24,33,32,13,17,27,22,44,34,34,27,35,28,24,25,33,30,46,27,25,24,16,20,16,26,26,15,25,27,22,27,26,16,24,27,12,12,24,12,42,27,27,27,27,18,20,17,27,23,37,23,24,21,16,24,16,26,26,26,26,13,16,22,36,26,26,21,54,24,18,45,26,24,26,26,13,13,22,22,26,26,47,23,37,20,18,44,26,21,25,12,17,26,26,26,26,26,26,20,43,21,27,26,16,26,20,18,26,17,17,15,29,30,13,16,13,22,27,33,35,35,24,30,30,30,30,30,30,40,28,25,25,25,25,13,13,13,13,32,34,34,34,34,34,34,26,35,33,33,33,33,25,27,27,25,25,25,25,25,25,40,22,26,26,26,26,12,12,12,12,27,27,27,27,27,27,27,26,28,27,27,27,27,24,27,24 };

SceneBase::SceneBase():
	im_parameters(),
	meshList(),
	im_vertexArrayID(0),
	im_programID(LoadShaders("Shaders//comg.vertexshader", "Shaders//comg.fragmentshader")),
	im_Cam(Cam()),
	modelStack(MS()),
	viewStack(MS()),
	projectionStack(MS()),
	bLightEnabled(false),
	elapsedTime(0.0f),
	FPS(0.0f)
{
	glClearColor(1.f, 0.82f, 0.86f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &im_vertexArrayID);
	glBindVertexArray(im_vertexArrayID);

	im_parameters[(int)UniType::MVP] = glGetUniformLocation(im_programID, "MVP");
	im_parameters[(int)UniType::MODELVIEW] = glGetUniformLocation(im_programID, "MV");
	im_parameters[(int)UniType::MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(im_programID, "MV_inverse_transpose");
	im_parameters[(int)UniType::MATERIAL_AMBIENT] = glGetUniformLocation(im_programID, "material.kAmbient");
	im_parameters[(int)UniType::MATERIAL_DIFFUSE] = glGetUniformLocation(im_programID, "material.kDiffuse");
	im_parameters[(int)UniType::MATERIAL_SPECULAR] = glGetUniformLocation(im_programID, "material.kSpecular");
	im_parameters[(int)UniType::MATERIAL_SHININESS] = glGetUniformLocation(im_programID, "material.kShininess");
	im_parameters[(int)UniType::COLOR_TEXTURE_ENABLED] = glGetUniformLocation(im_programID, "colorTextureEnabled");
	im_parameters[(int)UniType::COLOR_TEXTURE] = glGetUniformLocation(im_programID, "colorTexture");
	im_parameters[(int)UniType::TEXT_ENABLED] = glGetUniformLocation(im_programID, "textEnabled");
	im_parameters[(int)UniType::TEXT_COLOR] = glGetUniformLocation(im_programID, "textColor");

	glUseProgram(im_programID);
	glUniform1i(im_parameters[(int)UniType::TEXT_ENABLED], 0);

	for(int i = 0; i < (int)GeoType::Amt; ++i){
		meshList[i] = nullptr;
	}

	meshList[(int)GeoType::TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[(int)GeoType::TEXT]->textureID = LoadImg("Imgs//calibri.png");
	meshList[(int)GeoType::TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[(int)GeoType::DAY_BG] = MeshBuilder::GenerateSpriteAni("DayBG", 3, 5);
	meshList[(int)GeoType::DAY_BG]->textureID = LoadImg("Imgs//DayBG.png");
	meshList[(int)GeoType::NIGHT_BG] = MeshBuilder::GenerateSpriteAni("NightBG", 1, 5);
	meshList[(int)GeoType::NIGHT_BG]->textureID = LoadImg("Imgs//NightBG.png");
	static_cast<SpriteAni*>(meshList[(int)GeoType::DAY_BG])->AddAni("DayBG", 0, 12);
	static_cast<SpriteAni*>(meshList[(int)GeoType::DAY_BG])->Play("DayBG", -1, 1.0f);
	static_cast<SpriteAni*>(meshList[(int)GeoType::NIGHT_BG])->AddAni("NightBG", 0, 4);
	static_cast<SpriteAni*>(meshList[(int)GeoType::NIGHT_BG])->Play("NightBG", -1, 0.33f);
}

SceneBase::~SceneBase(){
	for(int i = 0; i < (int)GeoType::Amt; ++i){
		if(meshList[i]){
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	glDeleteProgram(im_programID);
	glDeleteVertexArrays(1, &im_vertexArrayID);
}

void SceneBase::Update(double dt){
	elapsedTime += (float)dt;
	FPS = (float)(1.f / dt);

	im_Cam.Update(dt);

	static int polyMode = GL_FILL;
	static bool isF2 = false;

	if(!isF2 && App::Key(VK_F2)){
		polyMode += polyMode == GL_FILL ? -2 : 1;
		glPolygonMode(GL_FRONT_AND_BACK, polyMode);
		isF2 = true;
	} else if(isF2 && !App::Key(VK_F2)){
		isF2 = false;
	}

	static_cast<SpriteAni*>(meshList[(int)GeoType::DAY_BG])->Update((float)dt);
	static_cast<SpriteAni*>(meshList[(int)GeoType::NIGHT_BG])->Update((float)dt);
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color, TextAlignment alignment){
	if(!mesh || mesh->textureID <= 0){
		return;
	}
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(im_parameters[(int)UniType::TEXT_ENABLED], 1);
	glUniform3fv(im_parameters[(int)UniType::TEXT_COLOR], 1, &color.r);
	glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE], 0);

	float textWidth = 0.0f;
	for(unsigned i = 0; i < text.length(); ++i){
		textWidth += (float)fontWidth[(unsigned)text[i]] / 64.0f;
	}

	float accum = 0;
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;

		if(alignment == TextAlignment::Right){
			characterSpacing.SetToTranslation(accum + 0.5f - textWidth, 0.5f, 0);
		} else if(alignment == TextAlignment::Center){
			characterSpacing.SetToTranslation(accum + 0.5f - textWidth * 0.5f, 0.5f, 0);
		} else{
			characterSpacing.SetToTranslation(accum + 0.5f, 0.5f, 0);
		}

		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(im_parameters[(int)UniType::MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);

		accum += (float)fontWidth[(unsigned)text[i]] / 64.0f;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(im_parameters[(int)UniType::TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, TextAlignment alignment){
	assert(mesh && mesh->textureID > 0);

	glDisable(GL_DEPTH_TEST);
	glUniform1i(im_parameters[(int)UniType::TEXT_ENABLED], 1);
	glUniform3fv(im_parameters[(int)UniType::TEXT_COLOR], 1, &color.r);
	glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE], 0);

	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0.0f);
	float textWidth = 0.0f;
	for(unsigned i = 0; i < text.length(); ++i){
		textWidth += (float)fontWidth[(unsigned)text[i]] / 64.0f;
	}
	modelStack.Scale(size, size, 1.0f);

	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	Mtx44 ortho;
	ortho.SetToOrtho(0.0f, (float)winWidth, 0.0f, (float)winHeight);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);

	float accum = 0.0f;
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;

		if(alignment == TextAlignment::Right){
			characterSpacing.SetToTranslation(accum + 0.5f - textWidth, 0.5f, 0);
		} else if(alignment == TextAlignment::Center){
			characterSpacing.SetToTranslation(accum + 0.5f - textWidth * 0.5f, 0.5f, 0);
		} else{
			characterSpacing.SetToTranslation(accum + 0.5f, 0.5f, 0);
		}

		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(im_parameters[(int)UniType::MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);

		accum += (float)fontWidth[(unsigned)text[i]] / 64.0f;
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(im_parameters[(int)UniType::TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight){
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(im_parameters[(int)UniType::MVP], 1, GL_FALSE, &MVP.a[0]);

	if(mesh->textureID > 0){
		glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(im_parameters[(int)UniType::COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.LoadIdentity();

	viewStack.LoadIdentity();
	viewStack.LookAt(
		im_Cam.pos.x, im_Cam.pos.y, im_Cam.pos.z,
		im_Cam.target.x, im_Cam.target.y, im_Cam.target.z,
		im_Cam.up.x, im_Cam.up.y, im_Cam.up.z
	);

	Mtx44 projection;
	projection.SetToOrtho(0.0f, (float)winWidth, 0.0f, (float)winHeight, -10.0f, 10.0f);
	projectionStack.LoadMatrix(projection);
}