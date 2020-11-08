#ifndef SCENE_H
#define SCENE_H

class Scene{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
};

#endif