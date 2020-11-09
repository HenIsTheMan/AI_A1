#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <assert.h>
#include <vector>

#include "Scene.h"
#include "Cam.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Vertex.h"

enum struct TextAlignment: int{
	Left,
	Center,
	Right,
	Amt
};

class SceneBase: public Scene{ //Abstract class
public:
	enum struct UniType: int{
		MVP,
		Text,
		UseTex,
		UseCustom,
		MyAlpha,
		Tex,
		TextColour,
		MyColour,
		Amt
	};
	enum struct GeoType: int{
		Text,
		DayBG,
		NightBG,
		Block,
		GridBG,
		GridLine,
		Skele,
		Reptile,
		Boy,
		Orc,
		Amt
	};

	virtual ~SceneBase();

	virtual void Update(double dt) override;
	virtual void Render() override;

	void RenderText(Mesh* mesh, std::string text, Color color, TextAlignment alignment = TextAlignment::Left); //Based on what model mats are alr in modelStack
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, TextAlignment alignment = TextAlignment::Left);
	void RenderMesh(const Mesh* const& mesh, const bool& useCustom = false, const Color& colour = Color(), const float& alpha = 1.0f);
protected:
	unsigned im_parameters[(int)UniType::Amt];
	Mesh* meshList[(int)GeoType::Amt];
	unsigned im_vertexArrayID;
	unsigned im_programID;

	Cam im_Cam;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	bool bLightEnabled;
	float elapsedTime;
	float FPS;

	SceneBase();
};

#endif