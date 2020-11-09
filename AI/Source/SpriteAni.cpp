#include "SpriteAni.h"

#include "GL\glew.h"
#include "Vertex.h"

SpriteAni::SpriteAni():
	SpriteAni(0, 0)
{
}

SpriteAni::SpriteAni(const int& rows, const int& cols):
	Mesh("notNeeded"),
	currTime(0.f),
	currFrame(0),
	rows(rows),
	cols(cols),
	playCount(0),
	currAni(""),
	allAnis({})
{
}

SpriteAni::~SpriteAni(){
	const auto& end = allAnis.end();
	for(auto iter = allAnis.begin(); iter != end; ++iter){
		if(iter->second){
			delete iter->second;
			iter->second = nullptr;
		}
	}
}

void SpriteAni::Play(const std::string& name, int repeat, float time){
	if(allAnis[name]){
		currAni = name;
		allAnis[name]->repeatCount = repeat;
		allAnis[name]->time = time;
		allAnis[name]->active = true;
	}
}

void SpriteAni::Resume(){
	allAnis[currAni]->active = true;
}

void SpriteAni::Pause(){
	allAnis[currAni]->active = false;
}

void SpriteAni::Reset(){
	currFrame = allAnis[currAni]->frames[0];
	playCount = 0;
}

void SpriteAni::AddAni(const std::string& name, const int& start, const int& end){
	Ani* ani = new Ani();
	for(int i = start; i < end; ++i){
		ani->frames.emplace_back(i);
	}
	allAnis[name] = ani; //Link ani to aniList
	if(currAni == ""){ //Set the curr ani if it does not exist
		currAni = name;
	}
	allAnis[name]->active = false;
}

void SpriteAni::AddSequenceAni(const std::string& name, const ::std::initializer_list<int>& frames){
	Ani* ani = new Ani();
	for(const int& frame: frames){
		ani->frames.emplace_back(frame);
	}
	allAnis[name] = ani; //...
	if(currAni == ""){ //...
		currAni = name;
	}
	allAnis[name]->active = false;
}

void SpriteAni::Update(float dt){
	if(allAnis[currAni]->active){ //Check if the curr Ani is active
		currTime += dt;
		int numFrame = (int)allAnis[currAni]->frames.size();
		float frameTime = allAnis[currAni]->time / numFrame;

		currFrame = allAnis[currAni]->frames[std::min((int)allAnis[currAni]->frames.size() - 1, int(currTime / frameTime))]; //Set curr frame based on curr time
		if(currTime >= allAnis[currAni]->time){ //If curr time >= total animated time...
			if(playCount < allAnis[currAni]->repeatCount){
				///Increase play count and repeat
				++playCount;
				currTime = 0;
				currFrame = allAnis[currAni]->frames[0];
			} else{ //If repeat count is 0 || play count == repeat count...
				allAnis[currAni]->active = false;
				allAnis[currAni]->ended = true;
			}
			if(allAnis[currAni]->repeatCount == -1){ //If ani is infinite...
				currTime = 0.f;
				currFrame = allAnis[currAni]->frames[0];
				allAnis[currAni]->active = true;
				allAnis[currAni]->ended = false;
			}
		}
	}
}

void SpriteAni::Render() const{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if(textureID > 0){
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}


	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if(mode == DRAW_MODE::DRAW_LINES){
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(currFrame * 6 * sizeof(GLuint)));
	} else if(mode == DRAW_MODE::DRAW_TRIANGLE_STRIP){
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(currFrame * 6 * sizeof(GLuint)));
	} else{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(currFrame * 6 * sizeof(GLuint)));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if(textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}
}