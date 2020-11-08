#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <assert.h>
#include <vector>

#include "Scene.h"
#include "Mtx44.h"
#include "Cam.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"
#include "GameObject.h"

class SceneBase: public Scene{
public:
	enum struct UniType: int{
		MVP,
		MODELVIEW,
		MODELVIEW_INVERSE_TRANSPOSE,
		MATERIAL_AMBIENT,
		MATERIAL_DIFFUSE,
		MATERIAL_SPECULAR,
		MATERIAL_SHININESS,
		COLOR_TEXTURE_ENABLED,
		COLOR_TEXTURE,
		TEXT_ENABLED,
		TEXT_COLOR,
		Amt
	};
	enum struct GeoType: int{
		TEXT,
		FISHTOOFULL,
		FISHFULL,
		FISHHUNGRY,
		FISHDEAD,
		SHARKCRAZY,
		SHARKNAUGHTY,
		SHARKHAPPY,
		FISHFOOD,
		DAY_BG,
		NIGHT_BG,
		Amt
	};

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
	unsigned im_vertexArrayID;
	Mesh* meshList[(int)GeoType::Amt];
	unsigned im_programID;
	unsigned im_parameters[(int)UniType::Amt];

	Cam im_Cam;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	bool bLightEnabled;

	float fps;
};

#endif