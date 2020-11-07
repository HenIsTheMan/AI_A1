#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <vector>

#include "Scene.h"
#include "Mtx44.h"
#include "Cam.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "GameObject.h"

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_BG,
		GEO_TARGET,

		GEO_FISHTOOFULL,
		GEO_FISHFULL,
		GEO_FISHHUNGRY,
		GEO_FISHDEAD,
		GEO_SHARKCRAZY,
		GEO_SHARKNAUGHTY,
		GEO_SHARKHAPPY,
		GEO_FISHFOOD,

		NUM_GEOMETRY,
	};
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Cam Cam;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	bool bLightEnabled;

	float fps;
};

#endif