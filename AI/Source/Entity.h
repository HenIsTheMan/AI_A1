#pragma once

#include "EntityAttribs.hpp"

class Entity final{
public:
	Entity();
	Entity(const EntityAttribs& attribs);
	~Entity() = default;

	Vector3& RetrieveLocalPos();
	Vector3& RetrieveLocalScale();

	///Getters
	const EntityType& GetType() const;
	const Vector3& GetLocalPos() const;
	const Vector3& GetLocalScale() const;

	///Setters
	void SetType(const EntityType type);
	void SetLocalPos(const Vector3& pos);
	void SetLocalPos(const float x, const float y, const float z);
	void SetLocalScale(const Vector3& scale);
	void SetLocalScale(const float x, const float y, const float z);
private:
	EntityAttribs im_Attribs;
};