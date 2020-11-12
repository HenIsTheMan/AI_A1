#pragma once

#include "EntityAttribs.hpp"

class Entity final{
public:
	Entity();
	Entity(const EntityAttribs& attribs);
	~Entity() = default;

	EntityType& RetrieveType();
	Vector3& RetrievePos();
	Vector3& RetrieveScale();

	///Getters
	const EntityType& GetType() const;
	const Vector3& GetPos() const;
	const Vector3& GetScale() const;

	///Setters
	void SetType(const EntityType type);
	void SetPos(const Vector3& pos);
	void SetPos(const float x, const float y, const float z);
	void SetScale(const Vector3& scale);
	void SetScale(const float x, const float y, const float z);
private:
	EntityAttribs im_Attribs;
};