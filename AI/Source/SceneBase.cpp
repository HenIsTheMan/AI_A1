#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.h"
#include "MeshBuilder.h"
#include "App.h"
#include "LoadImg.h"
#include <sstream>

static const int fontWidth[] = { 0,26,26,26,26,26,26,26,26,26,26,26,26,0,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,12,17,21,26,26,37,35,11,16,16,26,26,13,16,13,20,26,26,26,26,26,26,26,26,26,26,14,14,26,26,26,24,46,30,28,28,32,25,24,33,32,13,17,27,22,44,34,34,27,35,28,24,25,33,30,46,27,25,24,16,20,16,26,26,15,25,27,22,27,26,16,24,27,12,12,24,12,42,27,27,27,27,18,20,17,27,23,37,23,24,21,16,24,16,26,26,26,26,13,16,22,36,26,26,21,54,24,18,45,26,24,26,26,13,13,22,22,26,26,47,23,37,20,18,44,26,21,25,12,17,26,26,26,26,26,26,20,43,21,27,26,16,26,20,18,26,17,17,15,29,30,13,16,13,22,27,33,35,35,24,30,30,30,30,30,30,40,28,25,25,25,25,13,13,13,13,32,34,34,34,34,34,34,26,35,33,33,33,33,25,27,27,25,25,25,25,25,25,40,22,26,26,26,26,12,12,12,12,27,27,27,27,27,27,27,26,28,27,27,27,27,24,27,24 };

void SceneBase::Init(){
	glClearColor(1.f, 0.82f, 0.86f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &im_vertexArrayID);
	glBindVertexArray(im_vertexArrayID);

	im_programID = LoadShaders("Shaders//comg.vertexshader", "Shaders//comg.fragmentshader");
	
	// Get a handle for our uniform
	im_parameters[U_MVP] = glGetUniformLocation(im_programID, "MVP");
	//im_parameters[U_MODEL] = glGetUniformLocation(im_programID, "M");
	//im_parameters[U_VIEW] = glGetUniformLocation(im_programID, "V");
	im_parameters[U_MODELVIEW] = glGetUniformLocation(im_programID, "MV");
	im_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(im_programID, "MV_inverse_transpose");
	im_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(im_programID, "material.kAmbient");
	im_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(im_programID, "material.kDiffuse");
	im_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(im_programID, "material.kSpecular");
	im_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(im_programID, "material.kShininess");

	// Get a handle for our "colorTexture" uniform
	im_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(im_programID, "colorTextureEnabled");
	im_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(im_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	im_parameters[U_TEXT_ENABLED] = glGetUniformLocation(im_programID, "textEnabled");
	im_parameters[U_TEXT_COLOR] = glGetUniformLocation(im_programID, "textColor");
	
	glUseProgram(im_programID);
	
	glUniform1i(im_parameters[U_TEXT_ENABLED], 0);

	Cam.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 0), 10, 10, 1.f);
	meshList[GEO_TARGET] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 2.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadImg("Imgs//calibri.png");
	meshList[GEO_BG] = MeshBuilder::GenerateQuad("bg", Color(1, 1, 1));
	meshList[GEO_BG]->textureID = LoadImg("Imgs//grid20.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_FISHTOOFULL] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_FISHTOOFULL]->textureID = LoadImg("Imgs//toofull.tga");
	meshList[GEO_FISHFULL] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_FISHFULL]->textureID = LoadImg("Imgs//full.tga");
	meshList[GEO_FISHHUNGRY] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_FISHHUNGRY]->textureID = LoadImg("Imgs//hungry.tga");
	meshList[GEO_FISHDEAD] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_FISHDEAD]->textureID = LoadImg("Imgs//dead.tga");
	meshList[GEO_SHARKCRAZY] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_SHARKCRAZY]->textureID = LoadImg("Imgs//crazy.tga");
	meshList[GEO_SHARKNAUGHTY] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_SHARKNAUGHTY]->textureID = LoadImg("Imgs//shark.tga");
	meshList[GEO_SHARKHAPPY] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_SHARKHAPPY]->textureID = LoadImg("Imgs//happy.tga");
	meshList[GEO_FISHFOOD] = MeshBuilder::GenerateQuad("noNeed", Color(1, 1, 1));
	meshList[GEO_FISHFOOD]->textureID = LoadImg("Imgs//fishfood.tga");

	meshList[GEO_DAY_BG] = MeshBuilder::GenerateSpriteAni("DayBG", 3, 5);
	meshList[GEO_DAY_BG]->textureID = LoadImg("Image//DayBG.png");
	meshList[GEO_NIGHT_BG] = MeshBuilder::GenerateSpriteAni("NightBG", 1, 5);
	meshList[GEO_NIGHT_BG]->textureID = LoadImg("Image//NightBG.png");
	static_cast<SpriteAni*>(meshList[(int)GEO_DAY_BG])->AddAni("DayBG", 0, 12);
	static_cast<SpriteAni*>(meshList[(int)GEO_DAY_BG])->Play("DayBG", -1, 1.0f);
	static_cast<SpriteAni*>(meshList[(int)GEO_NIGHT_BG])->AddAni("NightBG", 0, 4);
	static_cast<SpriteAni*>(meshList[(int)GEO_NIGHT_BG])->Play("NightBG", -1, 0.33f);

	bLightEnabled = false;
}

void SceneBase::Update(double dt){
	static int polyMode = GL_FILL;
	static bool isF2 = false;

	if(!isF2 && App::Key(VK_F2)){
		polyMode += polyMode == GL_FILL ? -2 : 1;
		glPolygonMode(GL_FRONT_AND_BACK, polyMode);
		isF2 = true;
	} else if(isF2 && !App::Key(VK_F2)){
		isF2 = false;
	}

	static_cast<SpriteAni*>(meshList[(int)GEO_DAY_BG])->Update((float)dt);
	static_cast<SpriteAni*>(meshList[(int)GEO_NIGHT_BG])->Update((float)dt);
	
	fps = (float)(1.f / dt);
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color){
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(im_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(im_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(im_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(im_parameters[U_COLOR_TEXTURE], 0);
	float accum = 0;
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(accum, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(im_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
		accum += (float)fontWidth[(unsigned)text[i]] / 64;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(im_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(im_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(im_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(im_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(im_parameters[U_COLOR_TEXTURE], 0);
	float accum = 0;
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(accum + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(im_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);

		accum += (float)fontWidth[(unsigned)text[i]] / 64;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(im_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(im_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	if(mesh->textureID > 0)
	{
		glUniform1i(im_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(im_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(im_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneBase::Exit(){
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(im_programID);
	glDeleteVertexArrays(1, &im_vertexArrayID);
}