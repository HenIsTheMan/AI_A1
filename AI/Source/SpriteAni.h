#pragma once

#include <vector>
#include <unordered_map>

#include "Mesh.h"

class Ani final{
	friend class SpriteAni;
private:
	Ani():
		active(false),
		ended(false),
		time(0.f),
		repeatCount(0),
		name(""),
		frames({})
	{
	}

	bool active;
	bool ended;
	float time;
	int repeatCount;
	std::string name;
	std::vector<int> frames;
};

class SpriteAni final: public Mesh{
public:
	SpriteAni();
	SpriteAni(const int& rows, const int& cols);
	~SpriteAni();

	void Play(const std::string& name, int repeat, float time);
	void Pause();
	void Resume();
	void Reset();

	void AddAni(const std::string& name, const int& start, const int& end);
	void AddSequenceAni(const std::string& name, const ::std::initializer_list<int>& frames);
	void Update(float dt);
	void Render() const override;
private:
	float currTime;
	int currFrame;
	int rows;
	int cols;
	int playCount;
	std::string currAni;
	std::unordered_map<std::string, Ani*> allAnis;
};