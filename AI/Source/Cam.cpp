#include "Cam.h"
#include "App.h"
#include "Mtx44.h"

Cam::Cam()
{
	Reset();
}

Cam::~Cam()
{
}

void Cam::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

void Cam::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Cam::Update(double dt)
{
}