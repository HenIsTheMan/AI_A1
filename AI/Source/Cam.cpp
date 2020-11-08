#include "Cam.h"
#include "App.h"
#include "Mtx44.h"

Cam::Cam(){
	Reset();
}

void Cam::Reset(){
	pos.Set(0.0f, 0.0f, 1.0f);
	target.Set(0.0f, 0.0f, 0.0f);
	up.Set(0.0f, 1.0f, 0.0f);
}

void Cam::Update(double dt){
	const float camSpd = 50.0f;

	if(App::Key('R')){
		return Reset();
	}

	if(App::Key('W')){
		pos.y += camSpd * (float)dt;
		target.y += camSpd * (float)dt;
	}
	if(App::Key('S')){
		pos.y -= camSpd * (float)dt;
		target.y -= camSpd * (float)dt;
	}
	if(App::Key('D')){
		pos.x += camSpd * (float)dt;
		target.x += camSpd * (float)dt;
	}
	if(App::Key('A')){
		pos.x -= camSpd * (float)dt;
		target.x -= camSpd * (float)dt;
	}
}